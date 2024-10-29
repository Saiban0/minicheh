/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:30:29 by tom               #+#    #+#             */
/*   Updated: 2024/10/29 16:54:04 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_unset_arg(char	*arg, t_env	**env)
{
	int		i;
	char	**temp;

	i = -1;
	if (check_special_char(arg))
	{
		ft_putstr_fd("unset: ", STDERR_FILENO);
		ft_putstr_fd(arg, STDERR_FILENO);
		ft_putstr_fd(": invalid parameter name\n", STDERR_FILENO);
		return (false);
	}
	while ((*env)->envv[++i])
	{
		temp = ft_split((*env)->envv[i], '=');
		if (ft_strcmp(temp[0], arg) == 0)
		{
			free((*env)->envv[i]);
			(*env)->envv[i] = ft_strdup(" ");
			ft_free_double_array(temp);
			return (true);
		}
		ft_free_double_array(temp);
	}
	return (false);
}

void	rebuilt_envv(t_env	**env, int	size_of_new_env)
{
	int		i;
	int		j;
	char	**new_envv;

	new_envv = ft_calloc(size_of_new_env + 3, sizeof(char *));
	i = -1;
	j = 0;
	while ((*env)->envv[++i])
	{
		if ((*env)->envv[i][0] != ' ')
			new_envv[j++] = ft_strdup((*env)->envv[i]);
	}
	new_envv[j] = NULL;
	ft_free_double_array((*env)->envv);
	(*env)->envv = new_envv;
	return ;
}

void	ft_unset(char	**arg, t_env	**env)
{
	int		i;
	int		size_of_new_env;

	if (!*arg)
	{
		ft_putstr_fd("unset: not enough arguments\n", STDERR_FILENO);
		return ;
	}
	i = -1;
	size_of_new_env = double_array_size((*env)->envv);
	while (arg[++i])
	{
		if (check_unset_arg(arg[i], env))
			size_of_new_env--;
	}
	rebuilt_envv(env, size_of_new_env);
	return ;
}
