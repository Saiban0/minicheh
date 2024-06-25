/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:55:40 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	ft_memcmp(const void	*s1, const void	*s2, size_t	n)
{
	unsigned long	pos;
	int				tmp;

	pos = 0;
	while (pos < n)
	{
		tmp = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (tmp != 0)
			return (tmp);
		pos++;
	}
	return (0);
}
