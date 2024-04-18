/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:08 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/18 19:20:40 by idakhlao         ###   ########.fr       */
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
}

char	*parse_cmd(char **arg, t_pipex *pipex)
{
	char	*bin;
	char	*tmp;
	int		i;

	i = 0;
	while (pipex->path[i])
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

char	*getPathLine(char **envp)
{
	while (envp)
	{
		if (ft_strncmp(*envp, "PATH=", 5) == 0)
			return (*envp);
		envp++;
	}
	return (NULL);
}

char	**getPaths(char **envp)
{
	char	*tmp;
	char	**path;

	tmp = getPathLine(envp);
	if (!tmp)
		return (NULL);
	tmp += 5;
	path = ft_split(tmp, ':');
	if (!path)
		return (NULL);
	// printf("%s\n", tmp);
	return (path);
}

int	parsing(char **av, char **envp, t_pipex *pipex)
{
	pipex->args1 = ft_split(av[2], ' ');
	pipex->args2 = ft_split(av[3], ' ');
	if (!pipex->args1 || !pipex->args2)
		return (0);
	pipex->path = getPaths(envp);
	// printf("%s\n", pipex->path[0]);
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
	malloc_free(pipex->args1);
	malloc_free(pipex->args2);
	malloc_free(pipex->path);
	free(pipex->cmd1);
	free(pipex->cmd2);
	free(pipex);
}

void	execCmd1(t_pipex *pipex, char **av)
{
	// dup2()
	int fd;

	fd = open(av[4], O_WRONLY | O_CREAT, 0644);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	execve(pipex->cmd2, pipex->args2, NULL);
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	*pipex;

	if (ac != 5 || !av)
		return (wrong_args(1), -1);
	pipex = (t_pipex *)malloc(sizeof(t_pipex));
	if (!pipex)
		return (wrong_args(4), -1);
	if (parsing(av, envp, pipex) == -1)
	{
		free_tab(pipex);
		return (-1);
	}
	execCmd1(pipex, av);
	free_tab(pipex);
	return (0);
}
