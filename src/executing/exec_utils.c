/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:25:44 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/01 13:49:13 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_ast *cmd, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < cmd->nb_commands - 1)
	{
		close(pipex->pipe_fd[i][0]);
		close(pipex->pipe_fd[i][1]);
		i++;
	}
}

void	wait_execution(t_ast *cmd, int *status)
{
	if (cmd->right)
		wait_execution(cmd->right, status);
	if (cmd->left)
		wait_execution(cmd->left, status);
	waitpid(cmd->base->pid, status, 0);
}

void	create_fork(t_pipex *pipex, t_ast *cmd)
{
	cmd->base->pid = fork();
	if (cmd->base->pid == -1)
		error_management(e_fork_failure, cmd, pipex);
}

int	get_fd(char *file_name, bool read_or_write, t_ast *cmd, t_pipex *pipex)
{
	int	fd;

	fd = -1;
	if (ft_strcmp(file_name, "/dev/stdin"))
		return (STDIN_FILENO);
	if (ft_strcmp(file_name, "/dev/stdout"))
		return (STDOUT_FILENO);
	if (!read_or_write)
		fd = open(file_name, O_RDONLY);
	else
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		error_management(e_file, cmd, pipex);
	return (fd);
}
