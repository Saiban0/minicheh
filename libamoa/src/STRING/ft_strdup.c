/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:35:03 by ttaquet           #+#    #+#             */
/*   Updated: 2024/09/30 15:44:02 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		i;

	i = 0;
	dest = (char *)malloc(ft_strlen((char *)str) + 1);
	if (!(dest))
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
