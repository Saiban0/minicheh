/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:19:03 by tom               #+#    #+#             */
/*   Updated: 2024/11/05 18:08:22 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_pwd(char	**arg, t_env *env, t_ast *ast, t_pipex *pipex)
{
	if (arg != NULL)
	{
		if (arg[1])
		{
			ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
			return ;
		}
	}
	ft_putstr_fd(env->envv[env->pwd_position] + 4, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	g_exit_code = 0;
	ft_exit(NULL, ast, env, pipex);
}
