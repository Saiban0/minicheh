/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:54 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/27 15:45:42 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_switch(t_ast *cmd, char **envp)
{
	if (cmd->base->cmd[0][0] == '\0')
		error_management(e_empty_command, cmd);
	if (cmd->base->is_op)
	{
		// if (cmd->base->cmd_op == 1)
		// 	handle_pipe(cmd, envp);
		// if (cmd->base->cmd_op == 2)
		// 	handle_redirect_input(cmd, envp);
		// if (cmd->base->cmd_op == 3)
		// 	handle_redirect_output(cmd, envp);
	}
	// else if (cmd->base->builtins)
		// handle_builtins(cmd, envp);
	else if (cmd->base->cmd_op == 0)
		exec_extern(cmd, envp);
}

void	exec_extern(t_ast *cmd, char **envp)
{
	char	*cmd_path;
	pid_t	new_pid;
	int		status;

	cmd_path = ft_getpath(cmd->base->cmd[0]);
	new_pid = fork();
	if (new_pid == -1)
		error_management(e_fork_failure, cmd);
	if (new_pid == 0)
		exec_child(cmd, envp, cmd_path);
	waitpid(new_pid, &status, 0);
}

void	exec_child(t_ast *cmd, char **envp, char *cmd_path)
{
	if (execve(cmd_path, cmd->base->cmd, envp) == -1)
	{
		free(cmd_path);
		error_management(e_command_not_found, cmd);
	}
}
