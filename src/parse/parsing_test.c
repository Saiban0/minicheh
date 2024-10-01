/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:52:39 by tom               #+#    #+#             */
/*   Updated: 2024/09/30 14:59:17 by tom              ###   ########.fr       */
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
	command = rem_wspace(command);
	if (ft_strncmp(command,"echo", 4) == 0)
			return (e_echo);
	if (ft_strncmp(command,"cd", 2) == 0)
		return (e_cd);
	if (ft_strncmp(command,"pwd", 3) == 0)
			return (e_pwd);
	if (ft_strncmp(command,"export", 6) == 0)
			return (e_export);
	if (ft_strncmp(command,"unset", 5) == 0)
			return (e_unset);
	if (ft_strncmp(command,"exit", 4) == 0)
			return (e_exit);
	if (ft_strncmp(command,"env", 3) == 0)
			return (e_env);
	return (e_external_control);
}
