/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:54:00 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/20 14:10:52 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_bis(t_env *env)
{
	int	i;

	i = -1;
	env->pwd_position = -1;
	env->oldpwd_position = -1;
	env->home_position = -1;
	while (env->envv[++i])
	{
		if (ft_strncmp(env->envv[i], "PWD", 3) == 0)
		{
			env->pwd = ft_strdup(env->envv[i]);
			env->pwd_position = i;
		}
		if (ft_strncmp(env->envv[i], "OLDPWD", 6) == 0)
		{
			env->oldpwd = ft_strdup(env->envv[i]);
			env->oldpwd_position = i;
		}
		if (ft_strncmp(env->envv[i], "HOME", 4) == 0)
			env->home_position = i;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	i = -1;
	env = ft_calloc(1, sizeof(t_env));
	env->envv = ft_calloc(double_array_size(envp) + 1, sizeof(char *));
	if (envp && envp[0])
	{
		env->envp = true;
		while (envp[++i])
		{
			env->envv[i] = ft_strdup(envp[i]);
			if (errno == ENOMEM)
			{
				ft_free_double_array(env->envv);
				return (NULL);
			}
		}
		init_env_bis(env);
	}
	else
		env->envp = false;
	return (env);
}
