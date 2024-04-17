/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 18:13:00 by idakhlao          #+#    #+#             */
/*   Updated: 2024/04/17 14:19:29 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../includes/libft.h"
# include "../includes/ft_printf.h"
# include <errno.h>
# include <fcntl.h>

typedef struct s_pipex
{
	char	**path;
	char	**args1;
	char	**args2;
	char	*cmd1;
	char	*cmd2;
}	t_pipex;

#endif