/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:18:21 by idakhlao          #+#    #+#             */
/*   Updated: 2024/05/21 18:06:34 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	wrong_args(int nb)
{
	char	*s;

	if (nb == 1)
		ft_printf("FORMAT SHOULD BE [ ./pipex file1 cmd1 cmd2 cmd3\
		... cmdn file2]\n");
	else if (nb == 2)
		ft_printf("COMMAND DOES NOT EXIST\n");
	else if (nb == 3)
		ft_printf("FILE1 DOES NOT EXIST\n");
	else if (nb == 4)
		ft_printf("MEMORY ALLOCATION ERROR\n");
	else if (nb == 5)
		ft_printf("FD ERROR\n");
	else if (nb == 6)
		ft_printf("EXECUTION ERROR\n");
	else
	{
		s = "Error";
		perror(s);
		exit(EXIT_FAILURE);
	}
}

char	*get_pathline(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i]);
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

void	free_tab(t_bonus *pipex)
{
	if (pipex->args)
		malloc_free(*pipex->args);
	if (pipex->path)
		malloc_free(pipex->path);
	// if (pipex->cmd)
	// 	free(pipex->cmd);
}

void	close_fd(t_bonus *pipex, int fd)
{
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(fd);
}
