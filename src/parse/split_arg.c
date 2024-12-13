/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:07:13 by tom               #+#    #+#             */
/*   Updated: 2024/12/11 16:47:34 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	update_d_array(char **d_array, int i)
{
	char	*temp_str;

	temp_str = rem_wspace(d_array[i]);
	free(d_array[i]);
	d_array[i] = ft_strdup(temp_str);
	free(temp_str);
	return (1);
}

char	**clear_res(char **d_array)
{
	char	**res;
	int		temp_int;
	int		i;

	i = -1;
	temp_int = 0;
	if (only_wspace(d_array[0]))
	{
		ft_free_double_array(d_array);
		return (NULL);
	}
	while (d_array[++i])
		temp_int += update_d_array(d_array, i);
	i = -1;
	res = ft_calloc(temp_int + 2, sizeof(char *));
	temp_int = -1;
	while (d_array[++i])
		if (d_array[i][0] != ' ')
			res[++temp_int] = ft_strdup(d_array[i]);
	ft_free_double_array(d_array);
	return (res);
}

char	*test(int *tab_int, char *str, char **res)
{
	if (str[tab_int[0]] == '"' || str[tab_int[0]] == '\'')
	{
		tab_int[2] = quote_test(tab_int[0], tab_int[2], str);
		if (tab_int[2] == 0)
		{
			res[++tab_int[1]] = cuted(str, tab_int[0] - 1);
			if (res[tab_int[1]][0] == '"' || res[tab_int[1]][0] == '\'')
				res[tab_int[1]][0] = ' ';
			str += tab_int[0] + 1;
			tab_int[0] = -1;
		}
	}
	if (is_whitespace(str[tab_int[0]]) && tab_int[2] == 0)
	{
		while (is_whitespace(str[tab_int[0]]) && str[tab_int[0]])
			tab_int[0]++;
		res[++tab_int[1]] = cuted(str, tab_int[0] - 1);
		str += tab_int[0];
		tab_int[0] = -1;
	}
	return (str);
}

/*
	tab_int[0] = -1;  i
	tab_int[1] = -1;  j
	tab_int[2] = 0;   quote
*/
char	**ft_split_arg(char *str)
{
	int		len;
	char	**res;
	int		*tab_int;

	tab_int = ft_calloc(4, sizeof(int));
	tab_int[0] = -1;
	tab_int[1] = -1;
	tab_int[2] = 0;
	len = result_length(str);
	res = ft_calloc((len + 2), sizeof(char *));
	if (!res)
		return (NULL);
	while (str[++tab_int[0]] && tab_int[1] < len)
		str = test(tab_int, str, res);
	if (tab_int[1] < len)
	{
		tab_int[2] = quote_test(tab_int[0], tab_int[2], str);
		res[++tab_int[1]] = cuted(str, tab_int[0] - 1);
	}
	res[++tab_int[1]] = NULL;
	free(tab_int);
	res = clear_res(res);
	if (res == NULL)
		return (NULL);
	return (res);
}
