/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:50:27 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/10 17:07:22 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_ast *cmd, t_env *env)
{
	(void)env;
	if (cmd->base->cmd_op >= e_echo)
	{
		if (cmd->base->cmd_op == e_echo)
			ft_echo(cmd->base->cmd);
		// if (cmd->base->cmd_op == e_cd)
			// ft_cd();
		// if (cmd->base->cmd_op == e_pwd)
			// ft_pwd();
		// if (cmd->base->cmd_op == e_export)
		// 	ft_export();
		// if (cmd->base->cmd_op == e_unset)
		// 	ft_unset();
		// if (cmd->base->cmd_op == e_exit)
		// 	ft_exit();
		// if (cmd->base->cmd_op == e_env)
		// 	ft_env();
	}
}
