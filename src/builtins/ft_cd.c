/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:42:11 by tom               #+#    #+#             */
/*   Updated: 2024/08/13 19:04:54 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	update_pwd(t_ast	**ast)
// {
// 	t_env	**env;

// 	env = (*ast)->t_env;

// }

bool	ft_cd(char **arg)
{
	if (!arg[1])
		chdir ("~");
	else if (arg[2])
	{
		write(1, "cd: string not in pwd:", 23);
		write(1, arg[2], ft_strlen(arg[2]) + 1);
		return (false);
	}
	else if (arg[1])
	{
		if (chdir(arg[1]) == -1)
		{
			write(1, "cd: no such file or directory:", 31);
			write(1, arg[1], ft_strlen(arg[1]) + 1);
			return (false);
		}
	}
	// update_pwd(ast);
	return (true);
}
