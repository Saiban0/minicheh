/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:19:03 by tom               #+#    #+#             */
/*   Updated: 2024/10/11 12:22:55 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_pwd(char	**arg, t_env	*env)
{
	if (arg[1])
	{
		ft_putstr_fd("pwd: too many arguments\n", STDERR_FILENO);
		return ;
	}
	ft_putstr_fd(env->pwd, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return ;
}
