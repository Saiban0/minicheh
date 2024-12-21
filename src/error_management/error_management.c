/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:21:04 by bchedru           #+#    #+#             */
/*   Updated: 2024/12/21 16:03:42 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	error_free(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	(void)env;
	if (cmd)
		free_ast(pipex->ast_origin);
	if (pipex)
	{
		free(pipex);
		pipex = NULL;
	}
}

static void	error_management_bis(int error_code, t_ast *cmd, t_pipex *pipex,
		t_env *env)
{
	if (error_code == 4)
		ft_putstr_fd("minicheh : pipe failure\n", STDERR_FILENO);
	if (error_code == 6)
		ft_putstr_fd("minicheh : problem while searching in env\n",
			STDERR_FILENO);
	if (error_code == 7)
	{
		ft_putstr_fd("minicheh : malloc failure\n", STDERR_FILENO);
		g_exit_code = 2;
		ft_exit(NULL, cmd, env, pipex);
	}
}

void	error_management(t_error e_cod, t_ast *cmd, t_pipex *pipex, t_env *env)
{
	if (e_cod == 1)
	{
		ft_putstr_fd("minicheh: command not found: ", STDERR_FILENO);
		ft_putendl_fd(cmd->base->cmd[0], STDERR_FILENO);
		g_exit_code = CMDNOTFOUND;
		ft_exit(NULL, cmd, env, pipex);
	}
	if (e_cod == 2)
	{
		ft_putstr_fd("minicheh: can't open file\n", STDERR_FILENO);
		g_exit_code = 1;
		ft_exit(NULL, cmd, NULL, pipex);
	}
	if (e_cod == 3)
		ft_putstr_fd("minicheh : empty command\n", STDERR_FILENO);
	if (e_cod == 4)
	{
		ft_putstr_fd("minicheh : fork failure on command: ", STDERR_FILENO);
		ft_putendl_fd(cmd->base->cmd[0], STDERR_FILENO);
		ft_exit(NULL, cmd, env, pipex);
	}
	error_management_bis(e_cod, cmd, pipex, env);
	error_free(cmd, pipex, env);
}
