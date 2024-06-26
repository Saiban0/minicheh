/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:21:04 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/26 16:54:19 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_free(t_ast *cmd)
{
	if (cmd->left)
		error_free(cmd->left);
	if (cmd->right)
		error_free(cmd->right);
	if (cmd->base)
	{
		free(cmd->base->cmd);
		if (cmd->base->file_name)
			free(cmd->base->file_name);
		free(cmd->base);
	}
	free(cmd);
}

void	error_management(int error_code, t_ast *cmd)
{
	if (error_code == 0)
	{
		ft_putstr_fd("minicheh: command not found: ", 2);
		ft_putstr_fd(cmd->base->cmd, 2);
		error_free(cmd);
	}
	exit(0);
}
