/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:24:24 by idakhlao          #+#    #+#             */
/*   Updated: 2024/05/24 16:36:18 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

char	*parse_cmd(char *arg, t_bonus *pipex)
{
	char	*bin;
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	if (access(arg, F_OK | X_OK) == 0)
		return (ft_strdup(arg));
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
	i = 1;
	while (i < ac)
	{
		pipex->args[i - 1] = ft_split(av[i], ' ');
		i++;
	}
	pipex->args[i] = NULL;
	if (!pipex->args)
		return (-1);
	pipex->path = get_paths(envp);
	i = 1;
	j = 0;
	while (i < ac - 2)
	{
		pipex->cmd[j] = parse_cmd(pipex->args[i][0], pipex);
		if (pipex->cmd[j] == NULL)
			return (wrong_args(2), -1);
		i++;
		j++;
	}
	return (0);
}
// void	mid_children(t_bonus *pipex, char **av, char **envp)
// {
	// while (i < pipex->nb - 3)
	// {
	// 	pid = fork
	// }
// }

void	exec_cmd(t_bonus *pipex, char **av, char **envp)
{
	pid_t	pid;
	int		i;

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
	}
}

int	main(int ac, char **av, char **envp)
{
	t_bonus	pipex;

	if (ac < 5 || !av)
		return (wrong_args(1), -1);
	pipex.fd2 = open(av[ac - 1], O_WRONLY | O_CREAT, 0644);
	if (pipex.fd2 < 0)
	{
		free_tab(&pipex);
		wrong_args(0);
		return (0);
	}
	close(pipex.fd2);
	if (parsing(ac, av, envp, &pipex) == -1)
		return (free_tab(&pipex), -1);
	if (pipe(pipex.fd) == -1)
		return (0);
	// exec_cmd(&pipex, av, envp);
	// int i = 0;
	// int j;
	// while (pipex.args[i])
	// {
	// 	j = 0;
	// 	printf("i = %d\n", i);
	// 	while (pipex.args[i][j])
	// 	{
	// 		printf("[%s]\n", pipex.args[i][j]);
	// 		j++;
	// 	}
	// 	i++;
	// }
	// i = 0;
	// while (pipex.cmd[i])
	// {
	// 	printf("cmd: [%s]\n", pipex.cmd[i]);
	// 	i++;
	// }
	free_tab(&pipex);
}




// child                   1ere commande

// 			DUP2;
// child2                  toutes les commandes au milieu

// child3					derniere commande 		

// CODE PIPEX MADATORY

// WHILE (i < NB_COMMANDE A EXECUTER)
// {
// 			fork
// 			PIPE

// MULTI PIPE;