/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:54 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/26 18:32:14 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(t_ast *cmd, char **envp)
{
	char	*cmd_path;

	if (cmd->base->cmd[0][0] == '\0')
		exit(0);
	cmd_path = ft_getpath(cmd->base->cmd[0]);
	if (execve(cmd_path, cmd->base->cmd, envp) == -1)
	{
		free(cmd_path);
		error_management(e_command_not_found, cmd);
	}
}
