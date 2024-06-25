/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:26:54 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

void	*ft_memcpy(void	*dest, const void	*src, size_t	n)
{
	int	tmp;

	tmp = n;
	if (dest == NULL && src == NULL)
		return (dest);
	while (n > 0)
	{
		(*(unsigned char *)dest) = (*(unsigned char *)src);
		src++;
		dest++;
		n--;
	}
	dest -= tmp;
	return (dest);
}
