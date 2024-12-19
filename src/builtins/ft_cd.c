/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:10:19 by tom               #+#    #+#             */
/*   Updated: 2024/12/19 18:12:42 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tild_handler(char *pwd, char *str, char *home)
{
	(void)str;
	chdir(home);
	free(pwd);
	return (getcwd(NULL, 0));
}

bool	ft_cd(char	**arg, t_env	**env)
{
	char	*home;

	home = ft_strdup((*env)->envv[(*env)->home_position] + 5);
	if (!arg[1] || ft_strcmp(arg[1], "~")  == 0 || ft_strcmp(arg[1], "~/") == 0)
	{
		chdir(home);
		free((*env)->pwd);
		(*env)->pwd = getcwd(NULL, 0);
		free(home);
		return (true);
	}
	if (arg[1] && arg[2])
		return (cd_error(home, e_too_many_arg, NULL));
	if (arg[1][0] == '~')
		(*env)->pwd = tild_handler((*env)->pwd, arg[1]++, home);
	if (arg[1][0] == '/')
		arg[1]++;
	if (chdir(arg[1]) == 0)
	{
		free((*env)->pwd);
		(*env)->pwd = getcwd(NULL, 0);
		free(home);
		return (true);
	}
	return (cd_error(home, e_no_such_file_or_dir, arg[1]));
}
