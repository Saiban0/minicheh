/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:51:19 by tom               #+#    #+#             */
/*   Updated: 2024/10/11 12:08:17 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **arg, t_env	*env)
{
	int	i;

	i = -1;
	if (arg[1])
	{
		return ;
	}
	while (env->envv[++i])
	{
		ft_putstr_fd(env->envv[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
	return ;
}
