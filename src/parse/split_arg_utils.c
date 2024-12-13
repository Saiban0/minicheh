/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:13:14 by ttaquet           #+#    #+#             */
/*   Updated: 2024/12/13 15:49:32 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	result_length(char *str)
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
			quote = quote_test(i, quote, str);
			if (quote == 0)
				res++;
			is_sep = true;
		}
		else if (is_sep && !is_whitespace(str[i]) && quote <= 0 && res++)
			is_sep = false;
		if (is_whitespace(str[i]) && quote <= 0)
			is_sep = true;
	}
	return (res - 1);
}

/*
 * tab_int[0] = i;
 * tab_int[1] = j;
 * tab_int[2] = quote;
 */
int	*result_quote_tab(char *str, int *res)
{
	int		tab_int[3];
	bool	is_sep;

	tab_int[0] = -1;
	tab_int[1] = -1;
	tab_int[2] = 0;
	is_sep = true;
	res = ft_calloc(result_length(str) + 1, sizeof(int));
	while (str[++tab_int[0]])
	{
		if (str[tab_int[0]] == '"' || str[tab_int[0]] == '\'')
		{
			tab_int[2] = quote_test(tab_int[0], tab_int[2], str);
			if (tab_int[2] == 0)
				res[++tab_int[1]] = str[tab_int[0]];
		}
		else if (is_sep && !is_whitespace(str[tab_int[0]]) && tab_int[2] <= 0)
		{
			res[++tab_int[1]] = 0;
			is_sep = false;
		}
		if (is_whitespace(str[tab_int[0]]) && tab_int[2] <= 0)
			is_sep = true;
	}
	return (res);
}
