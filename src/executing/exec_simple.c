/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:54 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/23 17:55:06 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_switch(t_ast *cmd, t_env *env)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error_management(e_malloc_failure, cmd, pipex, env);
	ft_pipex_init(cmd, pipex, env);
	if (!cmd->base->is_op)
		if (!cmd->base->cmd[0][0])
			error_management(e_empty_command, cmd, pipex, env);
	if (cmd->base->is_op)
	{
		if (cmd->base->cmd_op == e_pipe)
			exec_handle_pipe(cmd, pipex, env);
		close_pipes(pipex, env);
		wait_execution(cmd, &(pipex->status));
	}
	else if (cmd->base->cmd_op == e_external_control || cmd->base->builtins)
		exec_simple(cmd, pipex, env);
	error_management(e_none, cmd, pipex, env);
}

static void	exec_only_child(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	if (cmd->base->builtins)
		exec_builtins(cmd, env, pipex);
	else
	{
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		if (cmd->base->path != NULL)
			execve(cmd->base->path, cmd->base->cmd, env->envv);
		error_management(e_command_not_found, cmd, pipex, env);
		exit(1);
	}
}

void	exec_simple(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int		status;

	if (!(cmd->base->cmd_op >= e_cd))
		create_fork(pipex, cmd);
	if (cmd->base->pid == 0)
	{
		search_redirects(cmd, pipex);
		if (pipex->in_fd != -1 || pipex->out_fd != -1)
			exec_simple_redirect(cmd, pipex, env);
		else
			exec_only_child(cmd, pipex, env);
	}
	waitpid(cmd->base->pid, &status, 0);
}

void	exec_simple_redirect(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	dup2(pipex->in_fd, STDIN_FILENO);
	dup2(pipex->out_fd, STDOUT_FILENO);
	close(pipex->in_fd);
	close(pipex->out_fd);
	exec_only_child(cmd, pipex, env);
}
