/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:24:24 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/04 17:33:23 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*parse_cmd(char *arg, t_bonus *pipex)
{
	char	*bin;
	char	*tmp;
	int		j;

	if (access(arg, F_OK | X_OK) == 0)
		return (ft_strdup(arg));
	int (i) = -1;
	while (++i < pipex->nb - 1)
	{
		j = -1;
		while (pipex->path && pipex->path[++j])
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
		}
	}
	return (NULL);
}

int	parsing(int ac, char **av, char **envp, t_bonus *pipex)
{
	int	i;
	int	j;

	if (access(av[1], F_OK | X_OK) != 0)
		return (ft_putendl_fd("Permission denied", 2), -2);
	init_pipex(pipex, ac);
	i = 0;
	while (++i < ac)
		pipex->args[i - 1] = ft_split(av[i], ' ');
	pipex->args[i] = NULL;
	if (!pipex->args)
		return (-1);
	pipex->path = get_paths(envp);
	i = pipex->index - 1;
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

int	here_doc(t_bonus *pipex, char *limiter, char **av, int ac)
{
	char	*line;
	char	*lim;

	if (ac < 6)
		return (wrong_args(3), -1);
	lim = ft_strjoin(limiter, "\n");
	if (!lim)
		return (wrong_args(0), -1);
	write(1, ">", 1);
	line = get_next_line(0);
	pipex->fd1 = open(av[1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	while (line)
	{
		if (ft_strcmp(lim, line) == 0)
		{
			printf("HEREEEEEE\n");
			return (free(line), free(lim), 0);
		}
		write(pipex->fd1, line, ft_strlen(line));
		free(line);
		write(1, ">", 1);
		line = get_next_line(0);
	}
	free(lim);
	return (0);
}

void	parse_heredoc(t_bonus pipex, int ac, char **av, char **envp)
{
	int	error;

	pipex.index = 3;
	error = parsing(ac, av, envp, &pipex);
	if (error == -1)
		return (free_tab(&pipex));
	else if (error == -2)
		return ;
	if (pipe(pipex.fd) == -1)
		return ;
	exec_cmd(&pipex, envp);
	unlink("here_doc");
}

int	main(int ac, char **av, char **envp)
{
	t_bonus	pipex;
	int		error;

	if (ac < 5 || !av)
		return (wrong_args(1), -1);
	pipex.fd2 = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (pipex.fd2 < 0)
		return (wrong_args(0), 0);
	close(pipex.fd2);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		parse_heredoc(pipex, ac, av, envp);
	else
	{
		pipex.index = 2;
		error = parsing(ac, av, envp, &pipex);
		if (error == -1)
			return (free_tab(&pipex), -1);
		else if (error == -2)
			return (-1);
		if (pipe(pipex.fd) == -1)
			return (0);
		exec_cmd(&pipex, envp);
	}
	free_tab(&pipex);
}
