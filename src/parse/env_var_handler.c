/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:14:57 by ttaquet           #+#    #+#             */
/*   Updated: 2024/11/25 20:12:30 by bchedru          ###   ########.fr       */
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

// Compte le nombre de caracteres au total dans le double tableau
// Il y a moyen que ca merde et compte les caractere nuls et donne un resultat plus grand que prevu
// J'ai pas teste parceque je sais pas comment tu comptes finir ta fonction env_var_handler
static int	caca_feur(char **array)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (array[i])
	{
		while (*array[i])
			j++;
		i++;
	}
	return (j);
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
	res = malloc(caca_feur(array) * sizeof(char));
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

	d_array_temp = ft_split_env_arg(rem_wspace((*ast)->base->cmd[i]),
			count_tab_size((*ast)->base->cmd[i]) + 1, (*env_start)->envv);
}
