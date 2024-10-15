/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 11:31:22 by tom               #+#    #+#             */
/*   Updated: 2024/10/15 17:45:38 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**double_array_cat(char	**tab1, char	**tab2)
{
	char	**res;
	int		i;
	int		j;

	res = ft_calloc(double_array_size(tab1) + double_array_size(tab2) + 1
			, sizeof(char *));
	i = -1;
	j = -1;
	while (tab1[++j])
		res[++i] = ft_strdup(tab1[j]);
	j = -1;
	while (tab2[++j])
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
			return (false);
	}
	return (true);
}

bool	only_char(char	*str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (false);
	return (true);
}

bool	export_error_handler(char	**temp, char	*error_message)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd(temp[0], STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_free_double_array(temp);
	return (false);
}

bool	ft_find(char	*arg, t_env	**env, char	**to_find)
{
	int		i;
	char	**temp;

	i = -1;
	while ((*env)->envv[++i])
	{
		temp = ft_split((*env)->envv[i], '=');
		if (ft_strcmp(to_find[0], temp[0]) == 0)
		{
			ft_free_double_array(temp);
			ft_free_double_array(to_find);
			free((*env)->envv[i]);
			(*env)->envv[i] = ft_strdup(arg);
			return (true);
		}
		ft_free_double_array(temp);
	}
	return (false);
}

bool	check_export_arg(char	*arg, t_env	**env)
{
	char	**temp;

	if (only_char(arg, '='))
		return (false);
	temp = ft_split(arg, '=');
	if (double_array_size(temp) == 1 && arg[ft_strlen(arg) - 1] != '=')
	{
		ft_free_double_array(temp);
		return (false);
	}
	if (!ft_isalpha(temp[0][0]))
		return(export_error_handler(temp, "not an identifier: "));
	if (!check_special_char(temp[0]))
		return(export_error_handler(temp, "not valid in this context: "));
	if (ft_find(arg, env, temp))
		return (false);
	ft_free_double_array(temp);
	return (true);
}

void	ft_export(char	**arg, t_env	**env)
{
	int		i;
	int		j;
	char	**arg_to_add;

	if (!*arg)
	{
		ft_putstr_fd("Usage : export [name]=[value]\n", STDERR_FILENO);
		return ;
	}
	i = -1;
	j = 0;
	arg_to_add = ft_calloc(double_array_size(arg) + 1, sizeof(char *));
	while (arg[++i])
		if (check_export_arg(arg[i], env))
			arg_to_add[j++] = ft_strdup(arg[i]);
	(*env)->envv = double_array_cat((*env)->envv, arg_to_add);
	return ;
}