/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:10:19 by tom               #+#    #+#             */
/*   Updated: 2024/10/11 15:39:01 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rev_cat(char *str_1, char *str_2, int to_free)
{
	char *res;

	res = ft_calloc(1, sizeof(char) * (ft_strlen(str_1) + ft_strlen(str_2) + 1));
	ft_strlcat(res, str_1, (ft_strlen(str_1) + 1));
	ft_strlcat(res, str_2, (ft_strlen(str_1) + ft_strlen(str_2) + 1));
	if (to_free == 2)
		free(str_2);
	else if (to_free == 1)
		free(str_1);
	return (res);
}

char	*remove_last_folder(char *pwd)
{
	int		i;
	char	*res;

	i = ft_strlen(pwd);
	while (pwd[--i] && pwd[i] != '/')
		pwd[i] = 0;
	pwd[i] = 0;
	res = ft_strdup(pwd);
	free(pwd);
	return (res);
}

void	update_pwd(t_env	**env, char	*path_update, char *home)
{
	int		i;
	char	*temp;
	char	**temp_tab;

	temp = ft_strdup((*env)->envv[(*env)->pwd_position] + 4);
	temp = ft_rev_cat("OLDPWD=", temp, 2);
	free((*env)->envv[(*env)->oldpwd_position]);
	(*env)->envv[(*env)->oldpwd_position] = ft_strdup(temp);
	free(temp);
	temp = ft_strdup((*env)->envv[(*env)->pwd_position] + 4);
	if (path_update[0] == '~')
	{
		free(temp);
		temp = ft_strdup(home);
	}
	temp_tab = ft_split(path_update, '/');
	i = -1;
	while (temp_tab[++i])
	{
		if (temp_tab[i][0] == '.' && temp_tab[i][1] == '.')
			temp = remove_last_folder(temp);
		else
		{
			temp = ft_rev_cat(temp, "/", 1);
			temp = ft_rev_cat(temp, temp_tab[i], 1);
		}
	}
	ft_free_double_array(temp_tab);
	free(temp);
	free(home);
}

bool	ft_cd(char	**arg, t_env	**env)
{
	//int		res = 0;
	char	*home;

	home = ft_strdup((*env)->envv[(*env)->home_position] + 5);
	(void)env;
	if (!arg[1])
	{
		chdir(home);
		update_pwd(env, "~", home);
		free(home);
		return (true);
	}
	arg[1] = rem_wspace(arg[1]);
	if (arg[1] && arg[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", STDERR_FILENO);
		ft_putstr_fd(arg[1], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		free(home);
		return (false);
	}
	if (chdir(arg[1]) == 0)
	{
		update_pwd(env, arg[1], home);
		return (true);
	}
	free(home);
	return (false);
}