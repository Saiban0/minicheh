/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:03:45 by tom               #+#    #+#             */
/*   Updated: 2024/07/10 14:56:02 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_to_print(char **double_array)
{
	int res;

	res = 0;
	while (*double_array)
		res += ft_strlen(*double_array++);
	ft_printf("%d\n", res);
	return (res);
}

char	*ft_echo(char **arg)
{
	char	*to_write;
	bool	flag;
	int		i;
	
	arg++;
	i = -1;
	flag = false;
	to_write = ft_calloc(1, 1);
	if (arg[0][0] == '-' && arg[0][1] == 'n')
	{
		flag = true;
		arg++;
	}
	while (arg[++i])
	{
		to_write = ft_strjoin(to_write, arg[i], 1);
		to_write[ft_strlen(to_write)] = ' ';
	}
	to_write[ft_strlen(to_write)] = 0;
	if (flag)
		to_write[ft_strlen(to_write) - 1] = 0;
	write(1, &(*to_write), ft_strlen(to_write) + 1);
	return (to_write);
}
