/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:33:42 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/04 17:34:17 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	init_pipex(t_bonus *pipex, int n)
{
	pipex->args = (char ***)malloc((n + 1) * sizeof(char **));
	pipex->args[0] = NULL;
	pipex->path = NULL;
	pipex->cmd = (char **)malloc((n - 2) * sizeof(char *));
	pipex->nb = n;
}
