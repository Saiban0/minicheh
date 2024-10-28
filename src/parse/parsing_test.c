/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:52:39 by tom               #+#    #+#             */
/*   Updated: 2024/10/25 15:30:38 by tom              ###   ########.fr       */
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
	t_cmd_and_op	res;

	if (ft_strncmp(command,"echo", 4) == 0)
		res = e_echo;
	else if (ft_strncmp(command,"cd", 2) == 0)
		res = e_cd;
	else if (ft_strncmp(command,"pwd", 3) == 0)
		res = e_pwd;
	else if (ft_strncmp(command,"export", 6) == 0)
		res = e_export;
	else if (ft_strncmp(command,"unset", 5) == 0)
		res = e_unset;
	else if (ft_strncmp(command,"exit", 4) == 0)
		res = e_exit;
	else if (ft_strncmp(command,"env", 3) == 0)
		res = e_env;
	else 
		res = e_external_control;
	return (res);
}
