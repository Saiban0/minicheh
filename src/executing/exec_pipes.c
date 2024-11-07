/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:07:12 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/05 20:30:18 by bchedru          ###   ########.fr       */
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
		child_execution(env->nb_commands - pipex->pipe_i, cmd, pipex, env);
	}
}

void	child_execution(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	if (curr_cmd == env->nb_commands - 1)
	{
		create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			last_exec(curr_cmd, cmd, pipex, env);
	}
	else if (curr_cmd == 0)
	{
		create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			first_exec(curr_cmd, cmd, pipex, env);
	}
	else
	{
		create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			middle_exec(curr_cmd, cmd, pipex, env);
	}
}

void	last_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	search_redirects(cmd, pipex, env);
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close_pipes(pipex, env);
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	if (cmd->base->builtins)
		exec_builtins(cmd, env, pipex);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex, env);
		g_exit_code = CMDNOTFOUND;
		exit(g_exit_code);
	}
}

void	middle_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	search_redirects(cmd, pipex, env);
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close_pipes(pipex, env);
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	if (cmd->base->builtins)
		exec_builtins(cmd, env, pipex);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex, env);
		g_exit_code = CMDNOTFOUND;
		exit(g_exit_code);
	}
}

void	first_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	search_redirects(cmd, pipex, env);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	close_pipes(pipex, env);
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
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex, env);
		g_exit_code = CMDNOTFOUND;
		exit(g_exit_code);
	}
}
