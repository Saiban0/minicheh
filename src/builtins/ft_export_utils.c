/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:08:21 by bchedru           #+#    #+#             */
/*   Updated: 2024/12/21 15:53:00 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*remove_quote(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		str_size;

	i = -1;
	j = -1;
	str_size = ft_strlen(str);
	while (str[++i])
		if (str[i] == '"')
			str_size--;
	res = ft_calloc(str_size + 1, sizeof(char));
	i = -1;
	while (str[++i])
	{
		if (str[i] == '"')
			continue ;
		else
			res[++j] = str[i];
	}
	return (res);
}

int	find_env_var_pos(char	*var, char	**envv)
{
	int		i;
	int		var_size;
	char	*var_tmp;

	i = -1;
	var += (var[0] == '$');
	var_size = ft_strlen(var);
	var_tmp = ft_calloc((var_size + 3), sizeof(char));
	ft_strlcat(var_tmp, var, var_size + 1);
	ft_strlcat(var_tmp, "=", var_size + 2);
	while (envv[++i])
	{
		if (ft_strncmp(var_tmp, envv[i], var_size + 1) == 0)
		{
			free(var_tmp);
			return (i);
		}
	}
	free(var_tmp);
	return (-1);
}

void	replace_env(t_env **env, char **arg_to_add)
{
	int		i;
	int		temp;
	char	**temp_arg;

	i = -1;
	while (arg_to_add[++i])
	{
		temp_arg = ft_split(arg_to_add[i], '=');
		temp = find_env_var_pos(temp_arg[0], (*env)->envv);
		if (temp != -1)
		{
			free((*env)->envv[temp]);
			(*env)->envv[temp] = ft_strdup(arg_to_add[i]);
			free(arg_to_add[i]);
			arg_to_add[i] = ft_strdup(" ");
		}
		ft_free_double_array(temp_arg);
	}
}
