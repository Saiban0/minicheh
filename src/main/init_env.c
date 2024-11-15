/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 16:54:00 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/12 16:58:07 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_env_bis(t_env *env)
{
	int	i;

	i = -1;
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
	env->quote = false;
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
	return (env);
}
