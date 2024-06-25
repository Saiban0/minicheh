/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 11:52:24 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	ft_countnum(long unsigned int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int					sign;
	char				*res;
	int					size;
	long unsigned int	tmp;

	if (n == 0)
		return (ft_strdup("0"));
	sign = n < 0;
	tmp = (long unsigned int)n * (((n > 0) * 2) - 1);
	size = ft_countnum(tmp);
	res = malloc((size + sign + 1) * sizeof(char));
	size -= !sign;
	if (!res)
		return (NULL);
	res[size + 1] = '\0';
	while (tmp > 0)
	{
		res[size--] = (tmp % 10) + '0';
		tmp /= 10;
	}
	if (sign)
		res[0] = '-';
	return (res);
}
