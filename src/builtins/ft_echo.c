/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:03:45 by tom               #+#    #+#             */
/*   Updated: 2024/12/27 16:44:12 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	empty_echo_handler(t_ast *cmd, t_env *env, t_pipex *pipex)
{
	g_exit_code = 0;
	write(1, "\n", 1);
	ft_exit(NULL, cmd, env, pipex);
}

void	ft_echo(char **arg, t_ast *cmd, t_env *env, t_pipex *pipex)
{
	bool	flag;
	int		i;

	arg++;
	i = -1;
	flag = false;
	if (!arg[0])
		empty_echo_handler(cmd, env, pipex);
	while (ft_strcmp(arg[0], "-n") == 0)
	{
		flag = true;
		arg++;
	}
	while (arg[++i])
	{
		ft_putstr_fd(arg[i], STDOUT_FILENO);
		if (arg[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == false)
		write(1, "\n", 1);
	g_exit_code = 0;
	ft_exit(NULL, cmd, env, pipex);
}
