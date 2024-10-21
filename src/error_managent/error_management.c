/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:21:04 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/21 20:10:28 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_free(t_ast *cmd, t_pipex *pipex)
{
	if (pipex)
	{
		if (pipex->pipe_fd)
			free(pipex->pipe_fd);
		free(pipex);
		pipex = NULL;
	}
	free_ast(cmd);
}

static void	error_management_bis(int error_code, t_ast *cmd, t_pipex *pipex)
{
	if (error_code == 4)
	{
		ft_putstr_fd("minicheh : pipe failure\n", STDERR_FILENO);
		error_free(cmd, pipex);
	}
	if (error_code == 6)
		ft_putstr_fd("minicheh : problem while searching in env\n",
			STDERR_FILENO);
	if (error_code == 7)
		ft_putstr_fd("minicheh : malloc failure\n", STDERR_FILENO);
}

void	error_management(int error_code, t_ast *cmd, t_pipex *pipex)
{
	if (error_code == 1)
	{
		ft_putstr_fd("minicheh: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->base->cmd[0], STDERR_FILENO);
	}
	if (error_code == 2)
	{
		ft_putstr_fd("minicheh: can't open file: ", STDERR_FILENO);
		ft_putendl_fd(cmd->right->right->base->file_name, STDERR_FILENO);
	}
	if (error_code == 3)
		ft_putstr_fd("minicheh : empty command\n", STDERR_FILENO);
	if (error_code == 4)
	{
		ft_putstr_fd("minicheh : fork failure on command: ", STDERR_FILENO);
		ft_putendl_fd(cmd->base->cmd[0], STDERR_FILENO);
		error_free(cmd, pipex);
	}
	error_management_bis(error_code, cmd, pipex);
	error_free(cmd, pipex);
}
