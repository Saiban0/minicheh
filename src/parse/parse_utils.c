/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:08 by tom               #+#    #+#             */
/*   Updated: 2024/10/22 20:19:54 by tom              ###   ########.fr       */
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
	res = ft_calloc(1, sizeof(char) * (j + 1));
	z = -1;
	i -= 1;
	while (command[++i] && i <= j)
		res[++z] = command[i];
	free(command);
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

int	result_length(char const *str, char c)
{
	int		i;
	int		res;
	bool	is_sep;
	int		quote;

	i = -1;
	quote = 0;
	res = 0;
	is_sep = true;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = quote_test(str[i], quote);
			if (quote == 0)
				res++;
		}
		else if (is_sep && str[i] != c && quote <= 0)
		{
			res++;
			is_sep = false;
		}
		if (str[i] == c && quote <= 0)
			is_sep = true;
	}
	return (res);
}

char	*cuted(char const *str, int end)
{
	char	*res;
	int		i;

	i = -1;
	res = ft_calloc(1, end + 2);
	while (str[++i] && i <= end)
		res[i] = str[i];
	res[i] = '\0';
	return (res);
}

char	**ft_split_arg(char const *str, char sep)
{
	int		len;
	char	**res;
	int		quote;
	int		i;
	int		j;

	i = -1;
	j = -1;
	quote = 0;
	len = result_length(str, sep);
	res = ft_calloc((len + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (str[++i] && j < len)
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = quote_test(str[i], quote);
			if (quote == 0)
			{
				res[++j] = cuted(str, i - 1);
				if (res[j][0] == '"' || res[j][0] == '\'')
					res[j][0] = ' ';
				res[j] = rem_wspace(res[j]);
				str += i + 1;
				i = -1;
			}
		}
		if (str[i] == sep && quote <= 0)
		{
			res[++j] = cuted(str, i - 1);
			str += i + 1;
			i = -1;
		}
	}
	res[++j] = NULL;
	return (res);
}
