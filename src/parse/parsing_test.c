/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:52:39 by tom               #+#    #+#             */
/*   Updated: 2024/10/24 16:53:29 by tom              ###   ########.fr       */
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
	char			*temp;
	t_cmd_and_op	res;

	temp = rem_wspace(command);
	if (ft_strncmp(temp,"echo", 4) == 0)
		res = e_echo;
	if (ft_strncmp(temp,"cd", 2) == 0)
		res = e_cd;
	if (ft_strncmp(temp,"pwd", 3) == 0)
		res = e_pwd;
	if (ft_strncmp(temp,"export", 6) == 0)
		res = e_export;
	if (ft_strncmp(temp,"unset", 5) == 0)
		res = e_unset;
	if (ft_strncmp(temp,"exit", 4) == 0)
		res = e_exit;
	if (ft_strncmp(temp,"env", 3) == 0)
		res = e_env;
	else 
		res = e_external_control;
	free(temp);
	return (res);
}
