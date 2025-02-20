/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:08 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/06 15:19:21 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*parse_cmd(char **arg, t_pipex *pipex)
{
	char	*bin;
	char	*tmp;
	int		i;

	i = 0;
	if (access(*arg, F_OK | X_OK) == 0)
		return (ft_strdup(*arg));
	while (pipex->path && pipex->path[i])
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		if (!tmp)
			return (NULL);
		bin = ft_strjoin(tmp, arg[0]);
		if (!bin)
			return (free(tmp), NULL);
		free(tmp);
		if (access(bin, F_OK | X_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

int	parsing(char **av, char **envp, t_pipex *pipex)
{
	init_pipex(pipex);
	pipex->args1 = ft_split(av[2], ' ');
	pipex->args2 = ft_split(av[3], ' ');
	if (!pipex->args1 || !pipex->args2)
		return (-1);
	printf("test\n\n");
	pipex->path = get_paths(envp);
	pipex->cmd1 = parse_cmd(pipex->args1, pipex);
	pipex->cmd2 = parse_cmd(pipex->args2, pipex);
	if (!pipex->cmd1 || !pipex->cmd2)
		return (wrong_args(2), -1);
	return (0);
}

void	child_process(t_pipex *pipex, char **av, char **envp)
{
	pipex->fd1 = open(av[1], O_RDONLY, 0644);
	if (pipex->fd1 == -1)
		return (free_tab(pipex), wrong_args(0));
	if (dup2(pipex->fd1, STDIN_FILENO) == -1
		|| dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		return (wrong_args(0));
	close(pipex->fd1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(pipex->cmd1, pipex->args1, envp) == -1)
		return (free_tab(pipex), wrong_args(0));
}

void	exec_cmd(t_pipex *pipex, char **av, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
		child_process(pipex, av, envp);
	pid = fork();
	if (pid == 0)
	{
		pipex->fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1
			|| dup2(pipex->fd2, STDOUT_FILENO) == -1)
			return (wrong_args(0));
		close(pipex->fd2);
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		if (execve(pipex->cmd2, pipex->args2, envp) == -1)
			return (free_tab(pipex), wrong_args(0));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;
	int		error;

	if (ac != 5 || !av)
		return (wrong_args(1), -1);
	pipex.fd2 = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (pipex.fd2 < 0)
		return (wrong_args(0), 0);
	close(pipex.fd2);
	error = parsing(av, envp, &pipex);
	if (error == -1)
		return (free_tab(&pipex), -1);
	else if (error == -2)
		return (-1);
	if (pipe(pipex.fd) == -1)
		return (0);
	exec_cmd(&pipex, av, envp);
	close(pipex.fd[1]);
	close(pipex.fd[0]);
	waitpid(0, NULL, 0);
	waitpid(0, NULL, 0);
	free_tab(&pipex);
	return (0);
}
