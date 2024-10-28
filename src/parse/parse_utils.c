/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:08 by tom               #+#    #+#             */
/*   Updated: 2024/10/25 16:08:41 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rem_wspace(char *command)
{
	int		i;
	int		j;
	int		z;
	char	*res;

	i = -1;
	j = -1;
	while (command[++i] && is_whitespace(command[i]))
		continue;
	j = ft_strlen(command);
	while (command[--j] && is_whitespace(command[j]))
		continue;
	res = ft_calloc(1, sizeof(char) * (j - i + 2));
	z = -1;
	while (command[i] && i <= j)
		res[++z] = command[i++];
	return (res);
}

int	quote_handler(char	*line, t_env	**env, int	quote_pos)
{
	if ((*env)->quote == 0)
	{
		(*env)->quote = line[quote_pos];
		ft_printf("quote open\n");
		return (1);
	}
	else if ((*env)->quote == line[quote_pos])
	{
		(*env)->quote = 0;
		ft_printf("quote close\n");
		return (2);
	}
	else if ((*env)->quote != 0 && (*env)->quote != line[quote_pos])
		return (3);
	return (0);
}

int	quote_test(int	c, int	quote)
{
	if (quote == 0)
		return (c);
	else if (quote == c)
		return (0);
	if (quote != 0 && c != quote)
		return (quote);
	return (-1);
}

bool	only_wspace(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_whitespace(str[i]))
			return (false);
	return (true);
}
