/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 13:54:26 by ttaquet           #+#    #+#             */
/*   Updated: 2024/12/17 15:43:39 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_arg_cut(int *tab_int, char **res, char *command, char **envv)
{
	char	*temp;

	if (command[tab_int[0]] == '$' && command[tab_int[0] + 1] != '(')
	{
		res[tab_int[1]] = ft_calloc(tab_int[0] + 2, sizeof(char));
		ft_strlcat(res[tab_int[1]++], command, tab_int[0] + 1);
		tab_int[2] = true;
		command += tab_int[0];
		tab_int[0] = 0;
	}
	else if ((is_whitespace(command[tab_int[0]])
			|| command[tab_int[0]] == '\'' || command[tab_int[0]] == '"')
		&& tab_int[2] == true)
	{
		temp = ft_calloc(tab_int[0] + 2, sizeof(char));
		ft_strlcat(temp, command, tab_int[0] + 1);
		res[tab_int[1]++] = find_env_var(temp, envv);
		free(temp);
		tab_int[2] = false;
		command += tab_int[0];
		tab_int[0] = 0;
	}
	tab_int[0] += 1;
	return (command);
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
	tab_int[0] = 0;
	tab_int[1] = 0;
	tab_int[2] = false;
	res = ft_calloc(res_size, 10 * sizeof(char *));
	while (command[tab_int[0]])
		command = split_arg_cut(tab_int, res, command, envv);
	if (command[0] == '$')
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

static int	join_size(char **array)
{
	int	i;
	int	j;
	int	res;

	i = -1;
	res = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
			res++;
	}
	return (res + 1);
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
	res = malloc(join_size(array) * sizeof(char));
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

	if ((*ast)->base->quote_tab[i] == '\'')
		return ;
	temp = ft_strdup((*ast)->base->cmd[i]);
	d_array_temp = ft_split_env_arg(temp,
			count_tab_size((*ast)->base->cmd[i]) + 1, (*env_start)->envv);
	free((*ast)->base->cmd[i]);
	free(temp);
	(*ast)->base->cmd[i] = ft_join_env_arg(d_array_temp);
}
