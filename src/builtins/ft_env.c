/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:51:19 by tom               #+#    #+#             */
/*   Updated: 2024/11/05 18:07:39 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_env(char **arg, t_env *env, t_ast *cmd, t_pipex *pipex)
{
	int	i;

	i = -1;
	if (arg[1])
	{
		ft_putstr_fd("env: too many arguments\n", STDERR_FILENO);
		return ;
	}
	while (env->envv[++i])
	{
		ft_putstr_fd(env->envv[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	g_exit_code = 0;
	ft_exit(NULL, cmd, env, pipex);
}
