/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:18:21 by idakhlao          #+#    #+#             */
/*   Updated: 2024/05/31 14:47:55 by idakhlao         ###   ########.fr       */
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
		ft_printf("FORMAT SHOULD BE [./pipex here_doc LIMITER cmd cmd2 file]\n");
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
	int	i;

	i = 0;
	if (pipex->args)
	{
		while (i < pipex->nb - 1)
		{
			malloc_free(pipex->args[i]);
			i++;
		}
		free(pipex->args);
	}
	if (pipex->path)
		malloc_free(pipex->path);
	if (pipex->cmd)
		malloc_free(pipex->cmd);
}

void	close_fd(t_bonus *pipex, int fd)
{
	close(pipex->fd[1]);
	close(pipex->fd[0]);
	close(fd);
}
