/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 11:09:15 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/04 14:02:58 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../includes/libft.h"
# include "../includes/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_bonus
{
	char	**path;
	char	***args;
	char	**cmd;
	int		nb;
	int		fd1;
	int		fd2;
	int		fd[2];
	int		index;
	int		pid;
}	t_bonus;

void	exec_cmd(t_bonus *pipex, char **envp);
void	wrong_args(int nb);
char	**get_paths(char **envp);
void	free_tab(t_bonus *pipex);
void	close_fd(t_bonus *pipex, int fd);
int		tab_size(char	**tab);

#endif