/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:18:08 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/13 15:22:53 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	parse_file1(char	**file)
{
	if (access(file, R_OK) == -1)
		return (-1);
	return (0);
}

int	parse_cmd(char	**cmd)
{
	char	*bin;
	char	*path;

	bin = "/bin/";
	path = ft_strjoin(bin, cmd[1]);
	if (!path)
		return (0);
	if (access(path, R_OK) == -1)
	{
		free(path);
		return (-1);
	}
	free(path);
}

int	parsing(char **av)
{
	char	**cmd1;

	cmd1 = av[2];
	parsecmd(cmd1);
}

void	wrong_args(int nb)
{
	if (nb == 1)
		ft_printf("FORMAT SHOULD BE [./pipex file1 cmd1 cmd2 file2]\n");
	if (nb == 2)
		ft_printf("COMMAND DOES NOT EXIST\n");
}

int	main(int ac, char **av)
{
	if (ac != 5 || !av)
		return (wrong_args(1), -1);
	if (parsing(av) == -1)
		return (wrong_args(2), -1);
	return (0);
}
