/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:52:39 by tom               #+#    #+#             */
/*   Updated: 2024/10/29 17:40:54 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_op(char	c)
{
	if (c == '|')
		return (true);
	else if (c == '<')
		return (true);
	else if (c == '>')
		return (true);
	return (false);
}

bool	is_whitespace(char	c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\n');
}

t_cmd_and_op	is_builtins(char *command)
{
	if	(command == NULL)
		return (e_test);
	else if	(command[0] == '\0')
		return (e_test);
	else if (ft_strncmp(command,"echo", 4) == 0)
		return (e_echo);
	else if (ft_strncmp(command,"cd", 2) == 0)
		return (e_cd);
	else if (ft_strncmp(command,"pwd", 3) == 0)
		return (e_pwd);
	else if (ft_strncmp(command,"export", 6) == 0)
		return (e_export);
	else if (ft_strncmp(command,"unset", 5) == 0)
		return (e_unset);
	else if (ft_strncmp(command,"exit", 4) == 0)
		return (e_exit);
	else if (ft_strncmp(command,"env", 3) == 0)
		return (e_env);
	else 
		return (e_external_control);
}
