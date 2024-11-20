/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:13:14 by ttaquet           #+#    #+#             */
/*   Updated: 2024/11/20 12:57:56 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	result_length(char const *str)
{
	int		i;
	int		res;
	bool	is_sep;
	int		quote;

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
