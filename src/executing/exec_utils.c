/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:25:44 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/12 22:28:22 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	exec_builtins(t_ast *cmd, t_env *env, t_pipex *pipex)
{
	if (cmd->base->cmd_op >= e_echo)
	{
		if (cmd->base->cmd_op == e_echo)
			ft_echo(cmd->base->cmd, cmd, env, pipex);
		if (cmd->base->cmd_op == e_cd)
			ft_cd(cmd->base->cmd, &env);
		if (cmd->base->cmd_op == e_pwd)
			ft_pwd(cmd->base->cmd, env, cmd, pipex);
		if (cmd->base->cmd_op == e_export)
			ft_export(cmd->base->cmd, &env);
		if (cmd->base->cmd_op == e_unset)
			ft_unset(cmd->base->cmd, &env);
		if (cmd->base->cmd_op == e_exit)
			ft_exit(NULL, cmd, env, pipex);
		if (cmd->base->cmd_op == e_env)
			ft_env(cmd->base->cmd, env, cmd, pipex);
	}
}

void	close_pipes(t_pipex *pipex)
{
	close(pipex->pipe_fd[0][0]);
	close(pipex->pipe_fd[0][1]);
	close(pipex->pipe_fd[1][0]);
	close(pipex->pipe_fd[1][1]);
}

void	create_fork(t_pipex *pipex, t_ast *cmd)
{
	cmd->base->pid = fork();
	if (cmd->base->pid == -1)
		error_management(e_fork_failure, cmd, pipex, NULL);
}

int	get_fd(char *file_name, int read_or_write, t_ast *cmd, t_pipex *pipex)
{
	int	fd;

	fd = -1;
	if (ft_strcmp(file_name, "/dev/stdin") == 0)
		return (STDIN_FILENO);
	if (ft_strcmp(file_name, "/dev/stdout") == 0)
		return (STDOUT_FILENO);
	if (read_or_write == 0)
		fd = open(file_name, O_RDONLY);
	if (read_or_write == 1)
		fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (read_or_write == 2)
		fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		error_management(e_file, cmd, pipex, NULL);
	return (fd);
}
