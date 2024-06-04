/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idakhlao <idakhlao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 18:28:11 by idakhlao          #+#    #+#             */
/*   Updated: 2024/06/04 18:55:31 by idakhlao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void	exec1(t_bonus *pipex, char **envp, int i)
{
	pipex->fd1 = open(pipex->args[0][0], O_RDONLY, 0644);
	if (pipex->fd1 == -1)
		return (free_tab(pipex), wrong_args(0));
	if (dup2(pipex->fd1, STDIN_FILENO) == -1
		|| dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		return (wrong_args(0));
	close(pipex->fd1);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(pipex->cmd[0], pipex->args[i - 1], envp) == -1)
		return (wrong_args(0));
}

void	exec3(t_bonus *pipex, char **envp, int size)
{
	pipex->fd2 = open(pipex->args[pipex->nb - 2][0], \
		O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->fd2 == -1)
		return (wrong_args(0));
	if (dup2(pipex->fd2, STDOUT_FILENO) == -1)
		return (wrong_args(0));
	close(pipex->fd2);
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(pipex->cmd[size], \
		pipex->args[pipex->nb - 3], envp) == -1)
		return (wrong_args(0));
}

void	exec2(t_bonus *pipex, char **envp, int j)
{
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		return (wrong_args(2));
	close(pipex->fd[0]);
	close(pipex->fd[1]);
	if (execve(pipex->cmd[j], pipex->args[j + 1], envp) == -1)
		return (wrong_args(1), wrong_args(0));
}

void	exec_pid(t_bonus *pipex, char **envp, int i, int j)
{
	int		size;

	size = tab_size(pipex->cmd) - 1;
	if (i == pipex->index)
		exec1(pipex, envp, i);
	else if (i == pipex->nb - 2)
		exec3(pipex, envp, size);
	else
		exec2(pipex, envp, j);
	if (dup2(pipex->fd[1], STDOUT_FILENO) == -1)
		return (wrong_args(0));
	close(pipex->fd[0]);
	close(pipex->fd[1]);
}

void	exec_cmd(t_bonus *pipex, char **envp)
{
	pid_t	pid;
	int		i;
	int		j;

	i = pipex->index;
	j = 0;
	while (i <= pipex->nb - 2)
	{
		if (pipe(pipex->fd) == -1)
			return (wrong_args(0));
		pid = fork();
		if (pid < 0)
			return (wrong_args(0));
		if (pid == 0)
			exec_pid(pipex, envp, i, j);
		if (dup2(pipex->fd[0], STDIN_FILENO) == -1)
			return (wrong_args(0));
		close(pipex->fd[0]);
		close(pipex->fd[1]);
		i++;
		j++;
	}
	while (wait(NULL) != -1)
		continue ;
}
