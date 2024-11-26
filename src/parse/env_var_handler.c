/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:14:57 by ttaquet           #+#    #+#             */
/*   Updated: 2024/11/26 16:49:53 by ttaquet          ###   ########.fr       */
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

bool	cut_var(char *command, int *tab_int, char **res, char **envv)
{
	char	*temp;

	if (command[tab_int[0]] == '$' && command[tab_int[0] + 1] != '(')
	{
		res[tab_int[1]] = ft_calloc(tab_int[0] + 2, sizeof(char));
		ft_strlcat(res[tab_int[1]++], command, tab_int[0] + 1);
		tab_int[2] = true;
		return (true);
	}
	else if (is_whitespace(command[tab_int[0]]) && tab_int[2] == true)
	{
		temp = ft_calloc(tab_int[0] + 1, sizeof(char));
		ft_strlcat(temp, command, tab_int[0] + 1);
		res[tab_int[1]++] = find_env_var(temp, envv);
		free(temp);
		tab_int[2] = false;
		return (true);
	}
	tab_int[0] += 1;
	return (false);
}
/*
 * tab_int[0] = i;
 * tab_int[1] = j;
 * tab_int[2] = env_var;
 */
char	**ft_split_env_arg(char *command, int res_size, char **envv)
{
	int		*tab_int;
	char	**res;

	tab_int = ft_calloc(4, sizeof(int));
	ft_bzero(tab_int, 2);
	tab_int[2] = false;
	res = ft_calloc(res_size + 1, sizeof(char *));
	while (command[tab_int[0]])
	{
		if (cut_var(command, tab_int, res, envv))
		{
			command += tab_int[0];
			tab_int[0] = 1;
		}
	}
	if (command[0] == '$' && command[1] != '(')
		res[tab_int[1]++] = find_env_var(command, envv);
	else
	{
		res[tab_int[1]] = ft_calloc(tab_int[0] + 1, sizeof(char));
		ft_strlcat(res[tab_int[1]++], command, tab_int[0] + 1);
	}
	res[tab_int[1]] = NULL;
	free(tab_int);
	return (res);
}

static int	count_char_darray(char **array)
{
	int	i;
	int	j;
	int res;

	i = 0;
	res = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j++])
			res++;
		i++;
	}
	return (res);
}

char	*ft_join_env_arg(char **array)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	res = ft_calloc(count_char_darray(array) + 2, sizeof(char));
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			res[k] = array[i][j];
			j++;
			k++;
		}
		free(array[i]);
		i++;
	}
	free(array);
	res[k] = '\0';
	return (res);
}

void	env_var_handler(t_ast **ast, t_env **env_start, int i)
{
	char	**d_array_temp;
	char	*temp;

	if ((*ast)->base->cmd[i][0] == '\'')
	{
		temp = ft_strdup((*ast)->base->cmd[i] + 1);
		free((*ast)->base->cmd[i]);
		(*ast)->base->cmd[i] = temp;
		return ;
	}
	if ((*ast)->base->cmd[i][0] == '"')
		(*ast)->base->cmd[i] += 1;
	if (ft_strrchr((*ast)->base->cmd[i], '$') == NULL)
		return ;
	temp = rem_wspace((*ast)->base->cmd[i]);
	d_array_temp = ft_split_env_arg(temp,
			count_tab_size((*ast)->base->cmd[i]) + 1, (*env_start)->envv);
	free((*ast)->base->cmd[i] - 1);
	free(temp);
	(*ast)->base->cmd[i] = ft_join_env_arg(d_array_temp);
}
