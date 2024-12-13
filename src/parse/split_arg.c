/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:07:13 by tom               #+#    #+#             */
/*   Updated: 2024/12/13 14:15:25 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cuted(char *str, int start, int end)
{
	char	*res;
	int		i;
	
	if (start > end)
		return (NULL);
	i = 0;
	res = ft_calloc(end - start + 2, sizeof(char));
	while (start <= end)
		res[i++] = str[start++];
	res[i] = '\0';
	return (res);
}

/*
	tab_int[0] = i;
	tab_int[1] = x;
	tab_int[2] = j;
	tab_int[3] = quote;
	tab_int[4] = is_sep;
 */
int	*init_tab_int(void)
{
	int	*tab_int;

	tab_int = ft_calloc(5, sizeof(int));
	tab_int[0] = -1;
	tab_int[1] = 0;
	tab_int[2] = -1;
	tab_int[3] = 0;
	tab_int[4] = true;
	return (tab_int);
}

void	split_quote_handler(char **res, int *tab_int, char *str)
{
	tab_int[3] = quote_test(tab_int[0], tab_int[3], str);
	if (tab_int[3] == 0)
		res[++tab_int[2]] = cuted(str, tab_int[1] + 1, tab_int[0] - 1);
	if (res[tab_int[2]] == NULL)
		res[tab_int[2]] = ft_strdup("");
	tab_int[1] = tab_int[0] + (tab_int[3] == 0);
}

char	**ft_split_arg(char *str)
{
	char	**res;
	int		*tab_int;
	
	tab_int = init_tab_int();
	res = ft_calloc(result_length(str) + 1, sizeof(char *));
	while (str[++tab_int[0]])
	{
		if (str[tab_int[0]] == '"' || str[tab_int[0]] == '\'')
			split_quote_handler(res, tab_int, str);
		else if (is_whitespace(str[tab_int[0]]) && tab_int[3] <= 0)
			tab_int[4] = 1;
		else if (tab_int[4] == 1 && tab_int[3] <= 0)
		{
			tab_int[1] = tab_int[0];
			while (str[tab_int[0]] && !is_whitespace(str[tab_int[0]])
				&& str[tab_int[0]] != '"' && str[tab_int[0]] != '\'')
				tab_int[0]++;
			tab_int[0]--;
			res[++tab_int[2]] = cuted(str, tab_int[1], tab_int[0]);
			tab_int[4] = 0;
		}
	}
	free(tab_int);
	return (res);
}
