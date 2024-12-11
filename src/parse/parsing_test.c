/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 02:52:39 by tom               #+#    #+#             */
/*   Updated: 2024/12/11 15:04:48 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_op(char c)
{
	if (c == '|')
		return (true);
	else if (c == '<')
		return (true);
	else if (c == '>')
		return (true);
	return (false);
}

bool	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\n');
}

int	ft_strcmp(char *str_a, char *str_b)
{
	int	i;

	i = 0;
	while (str_a[i] && str_b[i] && str_a[i] == str_b[i])
		i++;
	return (str_a[i] - str_b[i]);
}

t_cmd_and_op	is_builtins(char *command)
{
	if (command == NULL)
		return (e_empty);
	else if (command[0] == '\0')
		return (e_empty);
	else if (ft_strcmp(command, "echo") == 0)
		return (e_echo);
	else if (ft_strcmp(command, "cd") == 0)
		return (e_cd);
	else if (ft_strcmp(command, "pwd") == 0)
		return (e_pwd);
	else if (ft_strcmp(command, "export") == 0)
		return (e_export);
	else if (ft_strcmp(command, "unset") == 0)
		return (e_unset);
	else if (ft_strcmp(command, "exit") == 0)
		return (e_exit);
	else if (ft_strcmp(command, "env") == 0)
		return (e_env);
	else
		return (e_external_control);
}

bool	open_quote_pipe_test(char	*line)
{
	int		quote_pipe_res;

	if (only_wspace(line))
		return (false);
	quote_pipe_res = quote_pipe_check(line, true);
	if (only_wspace(line))
		return (false);
	if (quote_pipe_res == 0)
		return (true);
	return (false);
}
