/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:25:30 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	result_len(char const *str, char c)
{
	int	i;
	int	result;
	int	was_sep;

	i = 0;
	result = 0;
	was_sep = 1;
	while (str[i])
	{
		if (was_sep && str[i] != c)
		{
			result++;
			was_sep = 0;
		}
		if (str[i] == c)
			was_sep = 1;
		i++;
	}
	return (result);
}

char	*cut(char const *str, char sep, int start)
{
	int		len;
	char	*result;
	int		i;
	int		j;

	len = 0;
	i = start;
	while (str[i] && str[i++] != sep)
		len++;
	result = malloc((len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	j = 0;
	i = start;
	while (str[i] && str[i] != sep)
	{
		result[j] = str[i];
		i++;
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	**ft_split(char const *str, char sep)
{
	int		len;
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = result_len(str, sep);
	result = malloc((len + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	while (str[i] && j < len)
	{
		while (str[i] && str[i] == sep)
			i++;
		result[j] = cut(str, sep, i);
		j++;
		while (str[i] && str[i] != sep)
			i++;
	}
	result[j] = NULL;
	return (result);
}
