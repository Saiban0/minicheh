/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:07:13 by tom               #+#    #+#             */
/*   Updated: 2024/12/18 19:37:13 by ttaquet          ###   ########.fr       */
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
	tab_int[2] = 0;
	tab_int[3] = 0;
	tab_int[4] = true;
	return (tab_int);
}

void	split_quote_handler(char **res, int *tab_int, char *str)
{
	bool	is_cuted;

	is_cuted = false;
	tab_int[3] = quote_test(tab_int[0], tab_int[3], str);
	if (tab_int[3] != 0 && str[tab_int[0]] != tab_int[3])
		return ;
	if (tab_int[3] == 0)
	{
		res[tab_int[2]] = cuted(str, tab_int[1] + 1, tab_int[0] - 1);
		is_cuted = true;
	}
	if (res[tab_int[2]] == NULL && is_cuted)
		res[tab_int[2]] = ft_strdup("");
	if (is_cuted)
		tab_int[2]++;
	tab_int[1] = tab_int[0] + (tab_int[3] == 0);
	tab_int[4] = (tab_int[3] == 0);
}

char	**ft_split_arg(char *str)
{
	char	**res;
	int		*tab_int;

	tab_int = init_tab_int();
	res = ft_calloc(result_length(str) + 2, 10 * sizeof(char *));
	while (str[++tab_int[0]])
	{
		if (str[tab_int[0]] == '"' || str[tab_int[0]] == '\'')
			split_quote_handler(res, tab_int, str);
		else if (is_whitespace(str[tab_int[0]]) && tab_int[3] <= 0)
			tab_int[4] = true;
		else if (tab_int[4] == true && tab_int[3] <= 0)
		{
			tab_int[1] = tab_int[0];
			while (str[tab_int[0]] && !is_whitespace(str[tab_int[0]])
				&& str[tab_int[0]] != '"' && str[tab_int[0]] != '\'')
				tab_int[0]++;
			tab_int[0]--;
			res[tab_int[2]++] = cuted(str, tab_int[1], tab_int[0]);
			tab_int[4] = false;
		}
	}
	res[tab_int[2]] = NULL;
	free(tab_int);
	return (res);
}
