/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:13:00 by idakhlao          #+#    #+#             */
/*   Updated: 2024/05/15 15:25:55 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../includes/libft.h"
# include "../includes/ft_printf.h"
# include <errno.h>
# include <fcntl.h>
# include <sys/wait.h>
typedef struct s_pipex
{
	char	**path;
	char	**args1;
	char	**args2;
	char	*cmd1;
	char	*cmd2;
	int		fd1;
	int		fd2;
	int		fd[2];
}	t_pipex;

void	wrong_args(int nb);
char	**get_paths(char **envp);
void	free_tab(t_pipex *pipex);
void	close_fd(t_pipex *pipex, int fd);

#endif