/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 11:10:19 by tom               #+#    #+#             */
/*   Updated: 2024/10/11 11:19:40 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_cd(char	**arg)
{
	if (arg[1] && arg[2])
	{
		ft_putstr_fd("cd: string not in pwd: ", STDERR_FILENO);
		ft_putstr_fd(arg[1], STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		return (false);
	}
	if (chdir(arg[1]) == 0)
		return (true);
	ft_putstr_fd("cd: no such file or directory: ", STDERR_FILENO);
	ft_putstr_fd(arg[1], STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	return (false);
}