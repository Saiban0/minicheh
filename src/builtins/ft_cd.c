/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:10:19 by tom               #+#    #+#             */
/*   Updated: 2024/11/15 18:20:10 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_rev_cat(char *str_1, char *str_2, int to_free)
{
	char	*res;

	res = ft_calloc(1, sizeof(char) * (ft_strlen(str_1)
				+ ft_strlen(str_2) + 1));
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

	if (pwd[0] == '/')
		return (pwd);
	i = ft_strlen(pwd);
	while (pwd[--i] && pwd[i] != '/')
		pwd[i] = 0;
	pwd[i] = 0;
	res = ft_strdup(pwd);
	free(pwd);
	return (res);
}

char	*update_pwd_bis(char *temp, t_env **env)
{
	temp = ft_strdup((*env)->pwd + 4);
	temp = ft_rev_cat("OLDPWD=", temp, 2);
	free((*env)->oldpwd);
	(*env)->oldpwd = ft_strdup(temp);
	free(temp);
	return (ft_strdup((*env)->pwd + 4));
}

void	update_pwd(t_env	**env, char	*path_update, char *home)
{
	int		i;
	char	*temp;
	char	**temp_tab;

	temp = NULL;
	temp = update_pwd_bis(temp, env);
	if (path_update[0] == '~')
		free(temp);
	if (path_update[0] == '~')
		temp = ft_strdup(home + 5);
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
	free((*env)->pwd);
	(*env)->pwd = ft_rev_cat("PWD=", temp, 2);
	ft_free_double_array(temp_tab);
}

bool	ft_cd(char	**arg, t_env	**env)
{
	char	*home;
	char	*temp;

	home = ft_strdup((*env)->envv[(*env)->home_position] + 5);
	if (!arg[1])
	{
		chdir(home);
		update_pwd(env, "~", home);
		free(home);
		return (true);
	}
	temp = rem_wspace(arg[1]);
	free(arg[1]);
	arg[1] = temp;
	if (arg[1] && arg[2])
		return (cd_error(home, e_too_many_arg, NULL));
	if (chdir(arg[1]) == 0)
	{
		update_pwd(env, arg[1], home);
		free(home);
		return (true);
	}
	return (cd_error(home, e_no_such_file_or_dir, arg[1]));
}
