/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:13:14 by ttaquet           #+#    #+#             */
/*   Updated: 2024/12/17 15:43:01 by tom              ###   ########.fr       */
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
	res = 0;
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
	return (res);
}

int	*init_tabint(void)
{
	int	*tab_int;

	tab_int = ft_calloc(4, sizeof(int));
	tab_int[0] = -1;
	tab_int[1] = -1;
	tab_int[2] = 0;
	tab_int[3] = true;
	return (tab_int);
}

/*
 * tab_int[0] = i;
 * tab_int[1] = j;
 * tab_int[2] = quote;
 * tab_int[3] = is_sep;
 */
char	*result_quote_tab(char *str, char *res)
{
	int		*tab_int;

	tab_int = init_tabint();
	res = ft_calloc(result_length(str) + 1, sizeof(char));
	while (str[++tab_int[0]])
	{
		if (str[tab_int[0]] == '"' || str[tab_int[0]] == '\'')
		{
			tab_int[2] = quote_test(tab_int[0], tab_int[2], str);
			if (tab_int[2] == 0)
				res[++tab_int[1]] = str[tab_int[0]];
			tab_int[3] = (tab_int[2] == 0);
		}
		else if (tab_int[3] && !is_whitespace(str[tab_int[0]]) && tab_int[2] <= 0)
		{
			tab_int[3] = false;
			res[++tab_int[1]] = ' ';
		}
		if (is_whitespace(str[tab_int[0]]) && tab_int[2] <= 0)
			tab_int[3] = true;
	}
	res[++tab_int[1]] = 0;
	free(tab_int);
	return (res);
}
