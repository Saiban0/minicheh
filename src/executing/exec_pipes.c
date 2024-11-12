/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:07:12 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/08 04:52:23 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	exec_handle_pipe(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	if (cmd->right)
		exec_handle_pipe(cmd->right, pipex, env);
	if (cmd->left)
		exec_handle_pipe(cmd->left, pipex, env);
	if (cmd->base->cmd_op == e_external_control || cmd->base->builtins)
	{
		pipex->pipe_i++;
		pipe_execution(env->nb_commands - pipex->pipe_i, cmd, pipex, env);
	}
}

void	pipe_execution(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	const int	read_pipe = curr_cmd % 2;
	const int	write_pipe = (curr_cmd + 1) % 2;

	create_fork(pipex, cmd);
	if (cmd->base->pid == 0)
	{
		if (curr_cmd != 0)
		{
			dup2(pipex->pipe_fd[read_pipe][0], STDIN_FILENO);
			close(pipex->pipe_fd[read_pipe][0]);
		}
		if (curr_cmd != env->nb_commands - 1)
		{
			dup2(pipex->pipe_fd[write_pipe][1], STDOUT_FILENO);
			close(pipex->pipe_fd[write_pipe][0]);
		}
		close_pipes(pipex);
		child_execution(cmd, pipex, env);
	}
}

void	child_execution(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	search_redirects(cmd, pipex, env);
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	if (cmd->base->builtins)
		exec_builtins(cmd, env, pipex);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex, env);
		g_exit_code = CMDNOTFOUND;
		exit(g_exit_code);
	}
}
