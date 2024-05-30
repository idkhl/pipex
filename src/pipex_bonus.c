/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:24:24 by idakhlao          #+#    #+#             */
/*   Updated: 2024/05/30 17:03:34 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*parse_cmd(char *arg, t_bonus *pipex)
{
	char	*bin;
	char	*tmp;
	int		i;
	int		j;

	if (access(arg, F_OK | X_OK) == 0)
		return (ft_strdup(arg));
	i = 0;
	while (i < pipex->nb - 1)
	{
		j = 0;
		while (pipex->path && pipex->path[j])
		{
			tmp = ft_strjoin(pipex->path[j], "/");
			if (!tmp)
				return (NULL);
			bin = ft_strjoin(tmp, arg);
			if (!bin)
				return (free(tmp), NULL);
			free(tmp);
			if (access(bin, F_OK | X_OK) == 0)
				return (bin);
			free(bin);
			j++;
		}
		i++;
	}
	return (NULL);
}

void	init_pipex(t_bonus *pipex, int n)
{
	pipex->args = (char ***)malloc((n + 1) * sizeof(char **));
	pipex->path = NULL;
	pipex->cmd = (char **)malloc((n - 2) * sizeof(char *));
	pipex->nb = n;
}

int	parsing(int ac, char **av, char **envp, t_bonus *pipex)
{
	int	i;
	int	j;

	init_pipex(pipex, ac);
	i = 2; //multi  1, here_doc 2
	while (i < ac)
	{
		pipex->args[i - 1] = ft_split(av[i], ' ');
		// printf("args: %s\n", pipex->args[i - 1][0]);
		i++;
	}
	pipex->args[i] = NULL;
	if (!pipex->args)
		return (-1);
	pipex->path = get_paths(envp);
	i = 2; //multi  1, here_doc 2
	j = 0;
	while (i < ac - 2)
	{
		pipex->cmd[j] = parse_cmd(pipex->args[i][0], pipex);
		if (pipex->cmd[j] == NULL)
			return (wrong_args(2), -1);
		i++;
		j++;
	}
	pipex->cmd[j] = NULL;
	return (0);
}

void	exec_cmd(t_bonus *pipex, char **av, char **envp, int index)
{
	pid_t	pid;
	int		i;
	int		j;

	i = index;
	j = 0;
	while (i <= pipex->nb - 2)
	{
		if (pipe(pipex->fd) == -1)
			return (wrong_args(0));
		pid = fork();
		if (pid < 0)
			return (wrong_args(0));
		if (pid == 0)
		{
			if (i == index)
			{
				printf("CHILD 1\ncmd : %s\nargs : %s\n", pipex->cmd[0], pipex->args[i - 1][0]);
				pipex->fd1 = open(av[1], O_RDONLY, 0644);
				if (pipex->fd1 == -1)
					return (wrong_args(0));
				if (dup2(pipex->fd1, STDIN_FILENO) == -1
					|| dup2(pipex->fd[1], STDOUT_FILENO) == -1)
					return (wrong_args(0));
				close(pipex->fd1);
				close(pipex->fd[0]);
				close(pipex->fd[1]);
				if (execve(pipex->cmd[0], pipex->args[i - 1], envp) == -1)
					return (wrong_args(0));
			}
			else if (i == pipex->nb - 2)
			{
				printf("CHILD 3\ncmd : %s\nargs : %s\n", pipex->cmd[1], pipex->args[pipex->nb - 3][0]);
				pipex->fd2 = open(av[pipex->nb - 1], \
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (pipex->fd2 == -1)
					return (wrong_args(0));
				if (dup2(pipex->fd2, STDOUT_FILENO) == -1)
					return (wrong_args(0));
				close(pipex->fd2);
				close(pipex->fd[0]);
				close(pipex->fd[1]);
				if (execve(pipex->cmd[pipex->nb - 4], \
					pipex->args[pipex->nb - 3], envp) == -1)
					return (wrong_args(0));
			}
			else
			{
				printf("CHILD 2\ncmd : %s\nargs : %s\n", pipex->cmd[j], pipex->args[j + 1][0]);
				if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
					return (wrong_args(2));
				close(pipex->fd[0]);
				close(pipex->fd[1]);
				if (execve(pipex->cmd[j], pipex->args[j + 1], envp) == -1)
					return (wrong_args(1), wrong_args(0));
			}
			if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
				return (wrong_args(0));
			close(pipex->fd[0]);
			close(pipex->fd[1]);
		}
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			return (wrong_args(0));
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		i++;
		j++;
	}
	while (wait(NULL) != -1)
		continue ;
}

int	here_doc(t_bonus *pipex, char *limiter, char **av, int ac)
{
	char	*line;
	char	*lim;
	// pid_t	pid;

	if (ac < 6)
		return (wrong_args(3), printf("%d\n", ac), -1);
	lim = ft_strjoin(limiter, "\n");
	if (!lim)
		return (wrong_args(0), -1);
	// if (pipe(pipex->fd) == -1)
	// 	return (wrong_args(0), -1);
	// pid = fork();
	// printf("1\n");
	write(1, ">", 1);
	line = get_next_line(0);
	// printf("2\n");
	// if (pid == 0)
	// {
	// 	close(pipex->fd[0]);
	pipex->fd1 = open(av[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (line)
	{
		write(1, ">", 1);
		if (ft_strcmp(lim, line) == 0)
			return (0);
		// ft_putendl_fd(line, pipex->fd[1]);
		write(pipex->fd1, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
		// exit(1);
	// }
	// else
	// {
	// 	close(pipex->fd[1]);
	// 	dup2(pipex->fd[0], STDIN_FILENO);
	// 	wait(NULL);
	// }
	free(lim);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_bonus	pipex;
	int		i;

	if (ac < 5 || !av)
		return (wrong_args(1), -1);
	pipex.fd2 = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (pipex.fd2 < 0)
		return (wrong_args(0), 0);
	close(pipex.fd2);
	if (parsing(ac, av, envp, &pipex) == -1)
		return (free_tab(&pipex), -1);
	i = 0;
	int j;
	while (pipex.args[i])
	{
		j = 0;
		printf("i = %d\n", i);
		while (pipex.args[i][j])
		{
			printf("[%s]\n", pipex.args[i][j]);
			j++;
		}
		i++;
	}
	i = 0;
	while (pipex.cmd[i])
	{
		printf("cmd: [%s]\n", pipex.cmd[i]);
		i++;
	}
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
	{
		// if (parsing(ac, av, envp, &pipex) == -1)
		// 	return (free_tab(&pipex), -1);
		// printf("test\n");
		i = 3;
		if (here_doc(&pipex, av[2], av, ac) < 0)
			return (0);
		exec_cmd(&pipex, av, envp, i);
	}
	else
	{
		// if (parsing(ac, av, envp, &pipex) == -1)
		// 	return (free_tab(&pipex), -1);
		i = 2;
		exec_cmd(&pipex, av, envp, i);
	}
	free_tab(&pipex);
}
