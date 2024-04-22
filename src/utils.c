/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 11:18:21 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/22 12:03:34 by idakhlao         ###   ########.fr       */
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
	if (pipex->cmd2)
		free(pipex->cmd2);
	if (pipex)
		free(pipex);
}
