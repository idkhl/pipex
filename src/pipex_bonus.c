/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 16:24:24 by idakhlao          #+#    #+#             */
/*   Updated: 2024/05/21 20:07:38 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

// char	**parse_cmd(char ***arg, t_bonus *pipex)
// {
// 	char	*bin;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	if (access(*arg, F_OK | X_OK) == 0)
// 		return (ft_strdup(*arg));
// 	while (pipex->path && pipex->path[i])
// 	{
// 		tmp = ft_strjoin(pipex->path[i], "/");
// 		if (!tmp)
// 			return (NULL);
// 		bin = ft_strjoin(tmp, arg[0]);
// 		if (!bin)
// 			return (free(tmp), NULL);
// 		free(tmp);
// 		if (access(bin, F_OK | X_OK) == 0)
// 			return (bin);
// 		free(bin);
// 		i++;
// 	}
// 	return (NULL);
// }

void	init_pipex(t_bonus *pipex, int n)
{
	pipex->args = (char ***)malloc((n + 1) * sizeof(char **));
	pipex->path = NULL;
	pipex->cmd = NULL;
}

int	parsing(int ac, char **av, char **envp, t_bonus *pipex)
{
	int	i;

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
	// pipex->cmd = parse_cmd(pipex->args, pipex);
	// if (!pipex->cmd)
	return (0);
}

void	free_tabx(char **tab)
{
	int i = 0;

	if (!tab)
		return ;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	main(int ac, char **av, char **envp)
{
	t_bonus	pipex;

	if (ac < 5 || !av)
		return (wrong_args(1), -1);
	if (parsing(ac, av, envp, &pipex) == -1)
		return (free_tab(&pipex), -1);
	int i = 0;
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
	j = 0;
	// int k = 0
	if (pipex.args)
	{
		printf("1\n");
		while (i < ac - 1)
		{
			free_tabx(pipex.args[i]);
			i++;
		}
		free(pipex.args);
	}
	i = 0;
	free_tabx(pipex.path);
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