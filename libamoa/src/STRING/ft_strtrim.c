/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:17:09 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	in_str(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		size;
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = ft_strlen(s) - 1;
	while (in_str(s[i], set))
		i++;
	while (in_str(s[j], set))
		j--;
	if (i > j)
		return (ft_strdup(""));
	size = j - i;
	res = malloc(sizeof(char) * (size + 2));
	if (!res)
		return (NULL);
	while (i <= j)
	{
		*res = s[i];
		i++;
		res++;
	}
	*res = '\0';
	return (res - size - 1);
}
