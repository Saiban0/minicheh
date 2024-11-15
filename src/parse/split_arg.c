/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:07:13 by tom               #+#    #+#             */
/*   Updated: 2024/11/15 20:18:46 by ttaquet          ###   ########.fr       */
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
		else if (is_sep && str[i] != c && quote <= 0 && res++)
			is_sep = false;
		if (str[i] == c && quote <= 0)
			is_sep = true;
	}
	return (res - 1);
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

int	update_d_array(char **d_array, char *temp_str, int i)
{
	temp_str = rem_wspace(d_array[i]);
	free(d_array[i]);
	d_array[i] = ft_strdup(temp_str);
	free(temp_str);
	return (1);
}

char	**clear_res(char **d_array)
{
	char	**res;
	char	*temp_str;
	int		temp_int;
	int		i;

	i = -1;
	temp_int = 0;
	temp_str = NULL;
	while (d_array[++i])
	{
		if (only_wspace(d_array[i]))
			d_array[i][0] = ' ';
		else
			temp_int += update_d_array(d_array, temp_str, i);
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

char	*test(int *tab_int, char *str, char **res, char sep)
{
	if (str[tab_int[0]] == '"' || str[tab_int[0]] == '\'')
	{
		tab_int[2] = quote_test(str[tab_int[0]], tab_int[2]);
		if (tab_int[2] == 0)
		{
			res[++tab_int[1]] = cuted(str, tab_int[0] - 1);
			if (res[tab_int[1]][0] == '"' || res[tab_int[1]][0] == '\'')
				res[tab_int[1]][0] = ' ';
			str += tab_int[0] + 1;
			tab_int[0] = -1;
		}
	}
	if (str[tab_int[0]] == sep && tab_int[2] <= 0)
	{
		res[++tab_int[1]] = cuted(str, tab_int[0] - 1);
		str += tab_int[0] + 1;
		tab_int[0] = -1;
	}
	return (str);
}

char	**ft_split_arg(char *str, char sep)
{
	int		len;
	char	**res;
	int		*tab_int;

	tab_int = ft_calloc(4, sizeof(int));
	tab_int[0] = -1; // i
	tab_int[1] = -1; // j
	tab_int[2] = 0; // quote
	len = result_length(str, sep);
	res = ft_calloc((len + 2), sizeof(char *));
	if (!res)
		return (NULL);
	while (str[++tab_int[0]] && tab_int[1] < len)
		str = test(tab_int, str, res, sep);
	if (tab_int[1] < len)
	{
		tab_int[2] = quote_test(str[tab_int[0]], tab_int[2]);
		res[++tab_int[1]] = cuted(str, tab_int[0] - 1);
	}
	res[++tab_int[1]] = NULL;
	res = clear_res(res);
	free(tab_int);
	return (res);
}
