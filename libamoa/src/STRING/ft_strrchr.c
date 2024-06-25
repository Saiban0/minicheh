/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 18:07:33 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

char	*ft_strrchr(const char	*str, int c)
{
	int	i;
	int	tmp;

	tmp = -1;
	i = 0;
	while (str[i])
	{
		if (str[i] == c % 256)
			tmp = i;
		i++;
	}
	if (tmp == -1)
	{
		if ((unsigned char)c == '\0')
			return ((char *)str + i);
		return (NULL);
	}
	return ((char *)str + tmp);
}
