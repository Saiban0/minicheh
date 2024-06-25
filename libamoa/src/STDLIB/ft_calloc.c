/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 13:26:06 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

void	*ft_calloc(size_t	nmemb, size_t	size)
{
	unsigned char	*bmem;
	size_t			i;

	i = 0;
	bmem = malloc((nmemb) * size);
	if (!bmem)
		return (NULL);
	while (i < (nmemb) * size)
	{
		bmem[i] = 0;
		i++;
	}
	return ((void *) bmem);
}
