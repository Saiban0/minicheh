/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 16:34:28 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

int	ft_print_ptr(void	*ptr)
{
	if (ptr == NULL)
		return (write(1, "(nil)", 5));
	ft_putstr_fd("0x", 1);
	return (2 + ft_print_nbr_base (*(size_t *)& ptr, "0123456789abcdef"));
}

int	ft_print_args(char *str)
{
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_printnbr(int n)
{
	int			i;
	long int	num;

	i = (n < 0) + 1;
	ft_putnbr_fd(n, 1);
	num = (long int)n;
	num *= (((n > 0) * 2) - 1);
	while (num >= 10)
	{
		num /= 10;
		i++;
	}
	return (i);
}

int	ft_print_nbr_base(size_t n, char	*base)
{
	int	i;

	i = 0;
	ft_putnbr_base_fd(n, base, 1);
	while (n >= ft_strlen(base))
	{
		n /= ft_strlen(base);
		i++;
	}
	return (i + 1);
}
