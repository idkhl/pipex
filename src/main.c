/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:08 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/15 17:53:32 by idakhlao         ###   ########.fr       */
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
}

int	parse_cmd(char **arg)
{
	char	*bin;
	char	*path;
	char	**cmd;

	cmd = ft_split(*arg, ' ');
	if (!cmd)
		return (-1);
	printf("%s\n", cmd[0]);
	bin = "/bin/";
	path = ft_strjoin(bin, cmd[0]);
	malloc_free(cmd);
	if (!path)
		return (0);
	if (access(path, R_OK) == -1)
	{
		free(path);
		return (-1);
	}
	free(path);
	return (0);
}


int	parsing(char **av)
{
	if (access(av[1], R_OK) == -1)
		return (wrong_args(3), -1);
	if (parse_cmd(&av[2]) == -1 || parse_cmd(&av[3]) == -1)
		return (wrong_args(2), -1);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac != 5 || !av)
		return (wrong_args(1), -1);
	if (parsing(av) == -1)
		return (-1);
	// init_tab(av);
	return (0);
}
