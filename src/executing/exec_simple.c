/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:54 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/01 13:01:40 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_switch(t_ast *cmd, char **envp)
{
	t_pipex	*pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		error_management(e_malloc_failure, cmd, pipex);
	ft_pipex_init(cmd, pipex, envp);
	if (cmd->base->cmd[0][0] == '\0')
		error_management(e_empty_command, cmd, pipex);
	if (cmd->base->is_op)
	{
		// if (cmd->base->cmd_op == e_redirect_input)
		// 	handle_redirect_input(cmd, envp);
		// if (cmd->base->cmd_op == e_redirect_output)
		// 	handle_redirect_output(cmd, envp);
		if (cmd->base->cmd_op == e_pipe)
			exec_handle_pipe(cmd, pipex, envp);
		close_pipes(cmd, pipex);
		wait_execution(cmd, &(pipex->status));
	}
	else if (cmd->base->cmd_op == e_external_control)
		exec_simple(cmd, envp, pipex);
	error_management(e_none, cmd, pipex);
}

void	exec_simple(t_ast *cmd, char **envp, t_pipex *pipex)
{
	int		status;

	create_fork(pipex, cmd);
	if (cmd->base->pid == 0)
		exec_only_child(cmd, pipex, envp);
	waitpid(cmd->base->pid, &status, 0);
}

static void	exec_only_child(t_ast *cmd, t_pipex *pipex, char **envp)
{
	cmd->base->path = ft_getpath(cmd->base->cmd[0]);
	if (cmd->base->path != NULL)
		execve(cmd->base->path, cmd->base->cmd, envp);
	error_management(e_command_not_found, cmd, pipex);
}
