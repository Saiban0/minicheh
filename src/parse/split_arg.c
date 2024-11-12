/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:07:13 by tom               #+#    #+#             */
/*   Updated: 2024/11/07 14:50:58 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	**clear_res(char	**d_array)
{
	char	**res;
	char	*temp_str;
	int		temp_int;
	int		i;

	i = -1;
	temp_int = 0;
	while (d_array[++i])
	{
		if (only_wspace(d_array[i]))
			d_array[i][0] = ' ';
		else
		{
			temp_str = rem_wspace(d_array[i]);
			free(d_array[i]);
			d_array[i] = ft_strdup(temp_str);
			free(temp_str);
			temp_int++;
		}
	}
	i = -1;
	res = ft_calloc(temp_int + 2, sizeof(char *));
	temp_int = -1;
	while (d_array[++i])
		if (d_array[i][0] != ' ')
			res[++temp_int] = ft_strdup(d_array[i]);
	ft_free_double_array(d_array);
	return (res);
}

char	**ft_split_arg(char *str, char sep)
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
	res = ft_calloc((len + 2), sizeof(char *));
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
	if (j < len)
	{
		quote = quote_test(str[i], quote);
		res[++j] = cuted(str, i - 1);
	}
	res[++j] = NULL;
	res = clear_res(res);
	return (res);
}
