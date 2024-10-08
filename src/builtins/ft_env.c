/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:51:19 by tom               #+#    #+#             */
/*   Updated: 2024/09/30 15:56:37 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printenv(t_env	*env)
{
	int	i;

	i = -1;
	while (env->envv[++i])
	{
		write(1, env->envv[i], ft_strlen(env->envv[i]) + 1);
		write(1, "\n", 1);
	}
}

void	ft_env(char **arg, t_env	*env)
{
	if (!arg[1])
	{
		ft_printenv(env);
		return ;
	}
	return ;
}
