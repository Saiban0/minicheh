/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:31:22 by tom               #+#    #+#             */
/*   Updated: 2024/12/18 20:14:52 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**double_array_cat(char	**tab1, char	**tab2)
{
	char	**res;
	int		i;
	int		j;

	res = ft_calloc(double_array_size(tab1) + double_array_size(tab2) + 1,
			sizeof(char *));
	i = -1;
	j = -1;
	while (tab1[++j])
		if (ft_strcmp(tab1[j], " ") != 0)
			res[++i] = ft_strdup(tab1[j]);
	j = -1;
	while (tab2[++j])
		if (ft_strcmp(tab2[j], " ") != 0)
			res[++i] = ft_strdup(tab2[j]);
	ft_free_double_array(tab1);
	ft_free_double_array(tab2);
	return (res);
}

bool	check_special_char(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if ((str[i] >= '!' && str[i] <= '/') || (str[i] >= ':' && str[i] <= '@')
			|| (str[i] >= '[' && str[i] <= '`') || str[i] >= '{')
			return (true);
	}
	return (false);
}

bool	ft_find_export(char	*arg, t_env	**env, char	**arg_split)
{
	int		i;
	char	**temp;

	i = -1;
	while ((*env)->envv[++i])
	{
		temp = ft_split((*env)->envv[i], '=');
		if (ft_strcmp(arg_split[0], temp[0]) == 0)
		{
			ft_free_double_array(temp);
			ft_free_double_array(arg_split);
			free((*env)->envv[i]);
			(*env)->envv[i] = ft_strdup(arg);
			return (true);
		}
		ft_free_double_array(temp);
	}
	return (false);
}

int	check_export_arg(char **arg, int i)
{
	char	**temp;

	if (only_char(arg[i], '='))
		return (false);
	temp = ft_split(arg[i], '=');
	if (double_array_size(temp) == 1 && arg[i][ft_strlen(arg[i]) - 1] != '=')
	{
		ft_free_double_array(temp);
		return (false);
	}
	if (!ft_isalpha(temp[0][0]))
		return (export_error_handler(temp, "not an identifier: "));
	if (check_special_char(temp[0]))
		return (export_error_handler(temp, "not valid in this context: "));
	ft_free_double_array(temp);
	if (arg[i][ft_strlen(arg[i]) - 1] == '=' && arg[i + 1])
		return (-1);
	return (true);
}

void	ft_export(char **arg, t_env **env)
{
	int		i;
	int		j;
	int		temp;
	char	**arg_to_add;

	if (!*arg)
		return ((void)ft_putstr_fd("Usage : export [name]=[value]\n",
				STDERR_FILENO));
	i = -1;
	j = 0;
	arg_to_add = ft_calloc(double_array_size(arg) + 1, sizeof(char *));
	while (arg[++i])
	{
		temp = check_export_arg(arg, i);
		if (temp == true)
			arg_to_add[j++] = remove_quote(arg[i]);
		else if (temp == -1)
		{
			arg_to_add[j++] = ft_strjoin(arg[i], arg[i + 1], 0);
			i++;
		}
	}
	replace_env(env, arg_to_add);
	(*env)->envv = double_array_cat((*env)->envv, arg_to_add);
	return ;
}
