/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:03:45 by tom               #+#    #+#             */
/*   Updated: 2024/11/05 18:06:32 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	ft_echo(char **arg, t_ast *cmd, t_env *env, t_pipex *pipex)
{
	bool	flag;
	int		i;

	arg++;
	i = -1;
	flag = false;
	if (arg[0][0] == '-' && arg[0][1] == 'n')
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
	if (!flag)
		write(1, "\n", 1);
	g_exit_code = 0;
	ft_exit(NULL, cmd, env, pipex);
}
