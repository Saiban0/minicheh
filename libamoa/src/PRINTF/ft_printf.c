/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:48:16 by ttaquet           #+#    #+#             */
/*   Updated: 2024/01/22 17:03:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	get_args(va_list args, char c)
{
	if (c == 'c')
		return (ft_print_char(va_arg(args, int)));
	else if (c == 's')
		return (ft_print_args(va_arg(args, char *)));
	else if (c == 'p')
		return (ft_print_ptr(va_arg(args, void *)));
	else if (c == 'd' || c == 'i')
		return (ft_printnbr(va_arg(args, int)));
	else if (c == 'u')
		return (ft_print_nbr_base(va_arg(args, unsigned int), "0123456789"));
	else if (c == 'x')
		return (ft_print_nbr_base(va_arg(args, unsigned int),
				"0123456789abcdef"));
	else if (c == 'X')
		return (ft_print_nbr_base(va_arg(args, unsigned int),
				"0123456789ABCDEF"));
	else if (c == '%')
		return (ft_print_char(c));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	va_start(args, str);
	len = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += get_args(args, str[i + 1]);
			i += 2;
		}
		else
		{
			ft_putchar_fd(str[i++], 1);
			len++;
		}
	}
	return (len);
}
