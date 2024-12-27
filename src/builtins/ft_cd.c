/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:10:19 by tom               #+#    #+#             */
/*   Updated: 2024/12/27 16:31:48 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	basic_cd_handler(char *home, t_env **env)
{
	chdir(home);
	free((*env)->pwd);
	(*env)->pwd = getcwd(NULL, 0);
	free(home);
	return (true);
}

char	*tild_handler(char *pwd, char *str, char *home, int *temp)
{
	if (str[0] != '~')
		return (pwd);
	*temp += 1;
	chdir(home);
	free(pwd);
	str++;
	return (getcwd(NULL, 0));
}

bool	ft_cd(char	**arg, t_env	**env)
{
	char	*home;
	int		temp;

	temp = 0;
	home = ft_strdup((*env)->envv[(*env)->home_position] + 5);
	if (!arg[1] || ft_strcmp(arg[1], "~") == 0 || ft_strcmp(arg[1], "~/") == 0)
		return (basic_cd_handler(home, env));
	if (arg[1] && arg[2])
		return (cd_error(home, e_too_many_arg, NULL));
	(*env)->pwd = tild_handler((*env)->pwd, arg[1], home, &temp);
	temp += (arg[1][0] == '/') || (arg[1][1] == '/');
	arg[1] += temp;
	if (chdir(arg[1]) == 0)
	{
		arg[1] -= temp;
		free((*env)->pwd);
		(*env)->pwd = getcwd(NULL, 0);
		free(home);
		return (true);
	}
	arg[1] -= temp;
	return (cd_error(home, e_no_such_file_or_dir, arg[1]));
}
