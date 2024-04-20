/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:08 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/20 19:24:49 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	wrong_args(int nb)
{
	if (nb == 1)
		ft_printf("FORMAT SHOULD BE [./pipex file1 cmd1 cmd2 file2]\n");
	if (nb == 2)
		ft_printf("COMMAND DOES NOT EXIST\n");
	if (nb == 3)
		ft_printf("FILE1 DOES NOT EXIST\n");
	if (nb == 4)
		ft_printf("MEMORY ALLOCATION ERROR\n");
	if (nb == 5)
		ft_printf("FD ERROR\n");
	if (nb == 6)
		ft_printf("EXECUTION ERROR\n");
}

char	*parse_cmd(char **arg, t_pipex *pipex)
{
	char	*bin;
	char	*tmp;
	int		i;

	i = 0;
	while (pipex->path && pipex->path[i])
	{
		tmp = ft_strjoin(pipex->path[i], "/");
		bin = ft_strjoin(tmp, arg[0]);
		free(tmp);
		if (access(bin, F_OK | X_OK) == 0)
			return (bin);
		free(bin);
		i++;
	}
	return (NULL);
}

char	*get_pathline(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
			// return (*envp);
		// envp++;
		i++;
	}
	return (NULL);
}

char	**get_paths(char **envp)
{
	char	*tmp;
	char	**path;

	tmp = get_pathline(envp);
	if (!tmp)
		return (NULL);
	tmp += 5;
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
	return (path);
}

int	parsing(char **av, char **envp, t_pipex *pipex)
{
	access(av[4], F_OK);
	pipex->args1 = ft_split(av[2], ' ');
	pipex->args2 = ft_split(av[3], ' ');
	if (!pipex->args1 || !pipex->args2)
		return (0);
	pipex->path = get_paths(envp);
	pipex->cmd1 = parse_cmd(pipex->args1, pipex);
	pipex->cmd2 = parse_cmd(pipex->args2, pipex);
	if (access(av[1], R_OK) == -1)
		return (wrong_args(3), -1);
	if (!pipex->cmd1 || !pipex->cmd2)
		return (wrong_args(2), -1);
	return (0);
}

void	free_tab(t_pipex *pipex)
{
	if (pipex->args1)
		malloc_free(pipex->args1);
	if (pipex->args2)
		malloc_free(pipex->args2);
	if (pipex->path)
		malloc_free(pipex->path);
	if (pipex->cmd1)
		free(pipex->cmd1);
	if(pipex->cmd2)
		free(pipex->cmd2);
	if (pipex)
		free(pipex);
}

void	exec_cmd(t_pipex *pipex, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		pipex->fd1 = open("a", O_RDONLY);
		if (dup2(pipex->fd1, STDIN_FILENO) == -1 || dup2(pipex->fd[1], STDOUT_FILENO) == -1)
			return ;
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		close(pipex->fd1);
		if (execve(pipex->cmd1, pipex->args1, envp) == -1)
			return (wrong_args(6));
	}
	else
	{
		pipex->fd2 = open("fileqtqee3", O_WRONLY | O_CREAT, 0644);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1
			|| dup2(pipex->fd2, STDOUT_FILENO) == -1)
			return ;
		close(pipex->fd[1]);
		close(pipex->fd[0]);
		close(pipex->fd2);

		if (execve(pipex->cmd2, pipex->args2, envp) == -1)
			return (wrong_args(6));
	}
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;

	if (ac != 5 || !av)
		return (wrong_args(1), -1);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if(!envp || !*envp)
		return (-1);
	if (!pipex)
		return (wrong_args(4), -1);
	if (parsing(av, envp, pipex) == -1)
	{
		free_tab(pipex);
		return (-1);
	}
	// pipex->fd1 = open(av[1], O_RDONLY);
	pipex->fd2 = open(av[4], O_WRONLY | O_CREAT, 0644);
	// if (pipex->fd1 < 0 || pipex->fd2 < 0)
	if (pipex->fd2 < 0)
	{
		free_tab(pipex);
		wrong_args(5);
		return (0);
	}
	close(pipex->fd2);
	if (pipe(pipex->fd) == -1)
		return (0);
	exec_cmd(pipex, av);
	free_tab(pipex);
	return (0);
}
