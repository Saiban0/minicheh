/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:03:45 by tom               #+#    #+#             */
/*   Updated: 2024/10/11 11:44:51 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **arg)
{
	bool	flag;
	int		i;

	arg++;
	i = -1;
	flag = false;
	if (arg[0][0] == '-' && arg[0][1] == 'n')
	{
		flag = true;
		arg++;
	}
	while (arg[++i])
	{
		write(STDOUT_FILENO, arg[i], ft_strlen(arg[i]));
		write(STDOUT_FILENO, " ", 1);
	}
	if (!flag)
		write(1, "\n", 1);
}