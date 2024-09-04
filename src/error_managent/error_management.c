/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:21:04 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/28 16:22:26 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_free(t_ast *cmd)
{
	if (cmd->left)
		error_free(cmd->left);
	if (cmd->right)
		error_free(cmd->right);
	if (cmd->base)
	{
		if (cmd->base->cmd)
			ft_free_double_array(cmd->base->cmd);
		if (cmd->base->file_name)
			free(cmd->base->file_name);
		free(cmd->base);
	}
	free(cmd);
}

void	error_management(int error_code, t_ast *cmd)
{
	if (error_code == 1)
	{
		ft_putstr_fd("minicheh: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->base->cmd[0], STDERR_FILENO);
	}
	if (error_code == 2)
	{
		ft_putstr_fd("minicheh: file not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->base->cmd[0], STDERR_FILENO);
	}
	if (error_code == 3)
		ft_putstr_fd("minicheh : empty command\n", STDERR_FILENO);
	if (error_code == 4)
	{
		ft_putstr_fd("minicheh : fork failure on command: ", STDERR_FILENO);
		ft_putendl_fd(cmd->base->cmd[0], STDERR_FILENO);
		error_free(cmd);
		exit(-1);
	}
	if (error_code == 5)
	{
		ft_putstr_fd("minicheh : pipe failure\n", STDERR_FILENO);
		error_free(cmd);
		exit(-1);
	}
	error_free(cmd);
	exit(0);
}
