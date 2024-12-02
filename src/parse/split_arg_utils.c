/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:13:14 by ttaquet           #+#    #+#             */
/*   Updated: 2024/12/02 16:26:53 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	result_length(char const *str)
{
	int		i;
	int		res;
	int		quote;
	bool	is_sep;

	i = -1;
	quote = 0;
	res = 1;
	is_sep = true;
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = quote_test(str[i], quote);
			if (quote == 0)
				res++;
		}
		else if (is_sep && !is_whitespace(str[i]) && quote <= 0 && res++)
			is_sep = false;
		if (is_whitespace(str[i]) && quote <= 0)
			is_sep = true;
	}
	return (res - 1);
}

int *result_quote_tab(const char *str)
{
	int		*res;
	int		i;
	int		j;
	int		quote;
	bool	is_sep;

	j = -1;
	i = -1;
	quote = 0;
	is_sep = true;
	res = ft_calloc(result_length(str), sizeof(int));
	while (str[++i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			quote = quote_test(str[i], quote);
			if (quote == 0)
				res[++j] = str[i];
		}
		else if (is_sep && !is_whitespace(str[i]) && quote <= 0)
		{
			res[++j] = 0;
			is_sep = false;
		}
		if (is_whitespace(str[i]) && quote <= 0)
			is_sep = true;
	}
	return (res);
}
