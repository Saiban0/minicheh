/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:07:12 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/14 15:41:51 by bchedru          ###   ########.fr       */
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
		free(cmd->base->path);
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
	int	fd;

	search_redirects(cmd, pipex);
	fd = get_fd(pipex->out_file, 1, cmd, pipex);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	close_pipes(pipex, env);
	if (cmd->base->builtins)
		exec_builtins(cmd, env);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
	}
	error_management(e_command_not_found, cmd, pipex);
	exit(pipex->status);
}

void	middle_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	search_redirects(cmd, pipex);
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	close_pipes(pipex, env);
	if (cmd->base->builtins)
		exec_builtins(cmd, env);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
	}
	error_management(e_command_not_found, cmd, pipex);
	exit(pipex->status);
}

void	first_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int	fd;

	search_redirects(cmd, pipex);
	fd = get_fd(pipex->in_file, 0, cmd, pipex);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	close_pipes(pipex, env);
	if (cmd->base->builtins)
		exec_builtins(cmd, env);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
	}
	error_management(e_command_not_found, cmd, pipex);
	exit(pipex->status);
}
