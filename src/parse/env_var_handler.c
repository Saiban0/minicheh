/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:14:57 by ttaquet           #+#    #+#             */
/*   Updated: 2024/11/25 17:23:48 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int g_exit_code;

int	count_tab_size(char *command)
{
	int		i;
	int		res;
	bool	env_var;
	char	*temp;

	i = -1;
	res = 1;
	env_var = false;
	temp = rem_wspace(command);
	while (temp[++i])
	{
		if (temp[i] == '$' && temp[i + 1] != '(')
		{
			env_var = true;
			res++;
		}
		else if (is_whitespace(temp[i]) && env_var == true)
		{
			env_var = false;
			res++;
		}
	}
	free(temp);
	return (res);
}

char	**ft_split_env_arg(char *command, int res_size, char **envv)
{
	int		i;
	int		j;
	char	**res;
	bool	env_var;
	char	*temp;

	i = 0;
	j = 0;
	env_var = false;
	res = ft_calloc(res_size, sizeof(char *));
	while (command[i])
	{
		if (command[i] == '$' && command[i + 1] != '(')
		{
			res[j] = ft_calloc(i + 1, sizeof(char));
			ft_strlcat(res[j++], command, i);
			env_var = true;
			command += i;
			i = 0;
		}
		else if (is_whitespace(command[i]) && env_var == true)
		{
			temp = ft_calloc(i + 2, sizeof(char));
			ft_strlcat(temp, command, i + 1);
			res[j++] = find_env_var(temp, envv);
			free(temp);
			env_var = false;
			command += i;
			i = 0;
		}
		i++;
	}
	if (command[0] == '$')
		res[j++] = find_env_var(command, envv);
	else
	{
		res[j] = ft_calloc(i + 1, sizeof(char));
		ft_strlcat(res[j++], command, i + 1);
	}
	res[j] = NULL;
	ft_print_double_array(res);
	return (res);
}

void	env_var_handler(t_ast **ast, t_env **env_start, int i)
{
	char	**d_array_temp;

	d_array_temp = ft_split_env_arg(rem_wspace((*ast)->base->cmd[i]),
			count_tab_size((*ast)->base->cmd[i]) + 1, (*env_start)->envv);
}
