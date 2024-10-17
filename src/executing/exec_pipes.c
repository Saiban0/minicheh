/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:07:12 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/17 17:57:23 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_handle_pipe(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	if (cmd->right)
		exec_handle_pipe(cmd->right, pipex, env);
	if (cmd->left)
		exec_handle_pipe(cmd->left, pipex, env);
	if (cmd->base->cmd_op == e_external_control || cmd->base->builtins)
	{
		pipex->pipe_i++;
		child_execution(env->nb_commands - pipex->pipe_i, cmd, pipex, env);
	}
}

void	child_execution(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	if (curr_cmd == env->nb_commands - 1)
	{
		if (!(cmd->base->cmd_op == e_cd || cmd->base->cmd_op == e_export
				|| cmd->base->cmd_op == e_unset))
			create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			last_exec(curr_cmd, cmd, pipex, env);
	}
	else if (curr_cmd == 0)
	{
		if (!(cmd->base->cmd_op == e_cd || cmd->base->cmd_op == e_export
				|| cmd->base->cmd_op == e_unset))
			create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			first_exec(curr_cmd, cmd, pipex, env);
	}
	else
	{
		if (!(cmd->base->cmd_op == e_cd || cmd->base->cmd_op == e_export
				|| cmd->base->cmd_op == e_unset))
			create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			middle_exec(curr_cmd, cmd, pipex, env);
	}
}

void	last_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int	fd_in;
	int	fd_out;

	search_redirects(cmd, pipex);
	fd_in = get_fd(pipex->in_file, 0, cmd, pipex);
	fd_out = get_fd(pipex->out_file, 1, cmd, pipex);
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_pipes(pipex, env);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (cmd->base->builtins)
		exec_builtins(cmd, env);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex);
		exit(pipex->status);
	}
}

void	middle_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int	fd_in;
	int	fd_out;

	search_redirects(cmd, pipex);
	fd_in = get_fd(pipex->in_file, 0, cmd, pipex);
	fd_out = get_fd(pipex->out_file, 1, cmd, pipex);
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_pipes(pipex, env);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (cmd->base->builtins)
		exec_builtins(cmd, env);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex);
		exit(pipex->status);
	}
}

void	first_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int	fd_in;
	int	fd_out;

	search_redirects(cmd, pipex);
	fd_in = get_fd(pipex->in_file, 0, cmd, pipex);
	fd_out = get_fd(pipex->out_file, 1, cmd, pipex);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	close_pipes(pipex, env);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (cmd->base->builtins)
		exec_builtins(cmd, env);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex);
		exit(pipex->status);
	}
}
