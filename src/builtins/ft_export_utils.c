/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:08:21 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/20 17:36:07 by ttaquet          ###   ########.fr       */
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
