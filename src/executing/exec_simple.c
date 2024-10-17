/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:54 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/14 15:19:17 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_switch(t_ast *cmd, t_env *env)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error_management(e_malloc_failure, cmd, pipex);
	ft_pipex_init(cmd, pipex, env);
	if (!cmd->base->is_op)
		if (!cmd->base->cmd[0][0])
			error_management(e_empty_command, cmd, pipex);
	if (cmd->base->is_op)
	{
		if (cmd->base->cmd_op == e_pipe)
			exec_handle_pipe(cmd, pipex, env);
		close_pipes(pipex, env);
		wait_execution(cmd, &(pipex->status));
	}
	else if (cmd->base->cmd_op == e_external_control || cmd->base->builtins)
		exec_simple(cmd, pipex, env);
	error_management(e_none, cmd, pipex);
}

static void	exec_only_child(t_ast *cmd, t_pipex *pipex, t_env *env)
{
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

void	exec_simple(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int		status;

	search_redirects(cmd, pipex);
	if (!(cmd->base->cmd_op == e_cd || cmd->base->cmd_op == e_export
		|| cmd->base->cmd_op == e_unset))
		create_fork(pipex, cmd);
	if ((ft_strcmp(pipex->in_file, "/dev/stdin") != 0 || ft_strcmp(
		pipex->out_file, "/dev/stdout")) && cmd->base->pid == 0)
		exec_simple_redirect(cmd, pipex, env);
	if (cmd->base->pid == 0)
		exec_only_child(cmd, pipex, env);
	waitpid(cmd->base->pid, &status, 0);
}

void	exec_simple_redirect(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int	fd_out;
	int	fd_in;

	fd_in = get_fd(pipex->in_file, 0, cmd, pipex);
	fd_out = get_fd(pipex->out_file, 1, cmd, pipex);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	exec_only_child(cmd, pipex, env);
}
