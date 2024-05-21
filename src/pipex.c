/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:08 by idakhlao          #+#    #+#             */
/*   Updated: 2024/05/17 15:14:31 by idakhlao         ###   ########.fr       */
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

void	init_pipex(t_pipex	*pipex)
{
	pipex->args1 = NULL;
	pipex->args2 = NULL;
	pipex->path = NULL;
	pipex->cmd1 = NULL;
	pipex->cmd2 = NULL;
}

int	parsing(char **av, char **envp, t_pipex *pipex)
{
	init_pipex(pipex);
	// access(av[4], F_OK);
	pipex->args1 = ft_split(av[2], ' ');
	pipex->args2 = ft_split(av[3], ' ');
	pipex->path = NULL;
	if (!pipex->args1 || !pipex->args2)
		return (-1);
	pipex->path = get_paths(envp);
	pipex->cmd1 = parse_cmd(pipex->args1, pipex);
	pipex->cmd2 = parse_cmd(pipex->args2, pipex);
	// if (access(av[1], R_OK) == -1)
	// 	return (wrong_args(0), -1);
	if (!pipex->cmd1 || !pipex->cmd2)
		return (wrong_args(2), -1);
	// printf("%s\n", pipex->args1[0]);
	// printf("%s\n", pipex->args2[0]);
	// printf("%s\n", pipex->cmd1);
	// printf("%s\n", pipex->cmd2);
	// printf("%s\n", pipex->path[0]);
	return (0);
}

void	exec_cmd(t_pipex *pipex, char **av, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		pipex->fd1 = open(av[1], O_RDONLY, 0644);
		if (pipex->fd1 == -1)
		{
			wrong_args(0);
			return ;
		}
		if (dup2(pipex->fd1, STDIN_FILENO) == -1
			|| dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			return ;
		close(pipex->fd1);
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		if (execve(pipex->cmd1, pipex->args1, envp) == -1)
			return (wrong_args(0));
	}
	pid = fork();
	if (pid == 0)
	{
		pipex->fd2 = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1
			|| dup2(pipex->fd2, STDOUT_FILENO) == -1)
			return ;
		close(pipex->fd2);
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		if (execve(pipex->cmd2, pipex->args2, envp) == -1)
			return (wrong_args(0));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5 || !av)
		return (wrong_args(1), -1);
	pipex.fd2 = open(av[4], O_WRONLY | O_CREAT, 0644);
	if (pipex.fd2 < 0)
	{
		free_tab(&pipex);
		wrong_args(0);
		return (0);
	}
	close(pipex.fd2);
	if (parsing(av, envp, &pipex) == -1)
		return (free_tab(&pipex), -1);
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
