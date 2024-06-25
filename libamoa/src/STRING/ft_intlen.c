/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 13:59:21 by ttaquet           #+#    #+#             */
/*   Updated: 2024/04/10 18:47:33 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

size_t	ft_intlen(int number)
{
	size_t	res;
	int		sign;

	res = 0;
	sign = (number > 0);
	if (number == 0)
		return (1);
	while (number * ((sign * 2) - 1) > 0)
	{
		number = number / 10;
		res++;
	}
	return (res + (sign == 0));
}
