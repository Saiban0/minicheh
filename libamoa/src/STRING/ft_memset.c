/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:04:16 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

void	*ft_memset(void	*s, int c, size_t n)
{
	int	tmp;

	tmp = n;
	while (n > 0)
	{
		*(unsigned char *)s = c;
		s++;
		n--;
	}
	s = s - tmp;
	return (s);
}
