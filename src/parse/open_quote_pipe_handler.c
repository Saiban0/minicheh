/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quote_pipe_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:25:23 by tom               #+#    #+#             */
/*   Updated: 2024/12/11 16:54:32 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	unexpected_token_test(char *temp)
{
	int	i;
	int	op;

	i = -1;
	op = 0;
	while (temp[++i])
	{
		if (temp[i] == '|' || temp[i] == '>' || temp[i] == '<')
		{
			if (op == 1)
			{
				if (temp[i] == '|')
					return (parse_error_handler(e_unexp_pipe, NULL, false));
				if (temp[i] == '>')
					return (parse_error_handler(e_unexp_redir_output, NULL, false));
				if (temp[i] == '<')
					return (parse_error_handler(e_unexp_redir_input, NULL, false));
			}
			op = 1;
			if (temp[i + 1] == '|')
				return (parse_error_handler(e_unexp_pipe, NULL, false));
			else if (temp[i] == '<' && temp[i + 1] == '>')
				return (parse_error_handler(e_unexp_redir_output, NULL, false));
			else if (temp[i] == '>' && temp[i + 1] == '<')
				return (parse_error_handler(e_unexp_redir_input, NULL, false));
			else if (temp[i] == temp[i + 1] && temp[i - 1] == temp[i])
			{	
				if (temp[i] == '>')
					return (parse_error_handler(e_unexp_redir_output, NULL, false));
				if (temp[i] == '<')
					return (parse_error_handler(e_unexp_redir_input, NULL, false));
			}
			else if (temp[i] == temp[i + 1] && temp[i - 1] != temp[i])
				i++;
		}
		else if (!is_whitespace(temp[i]))
			op = 0;
	}
	if (temp[i - 1] == '|')
		return (parse_error_handler(e_unexp_pipe, NULL, false));
	if (temp[i - 1] == '>')
		return (parse_error_handler(e_unexp_redir_output, NULL, false));
	if (temp[i - 1] == '<')
		return (parse_error_handler(e_unexp_redir_input, NULL, false));
	return (true);
}

bool	redirect_pipe_first(char *temp)
{
	if (temp[0] == '|')
		parse_error_handler(e_unexp_pipe, NULL, false);
	else if (temp[0] == '<')
		parse_error_handler(e_unexp_redir_input, NULL, false);
	else if (temp[0] == '>')
		parse_error_handler(e_unexp_redir_output, NULL, false);
	else if (temp[0] == '|')
		parse_error_handler(e_unexp_pipe, NULL, false);
	else
		return (false);
	free(temp);
	return (true);
}

bool	pipe_end_line_test(char *line)
{
	char	*temp;
	int		i;

	i = 0;
	temp = rem_wspace(line);
	while (temp[i])
		i++;
	i = temp[i - 1];
	free(temp);
	if (i == '|')
		return (true);
	return (false);
}

int	quote_pipe_check(char	*line, bool first_test)
{
	int		i;
	int		quote;
	char	*temp;

	i = -1;
	quote = 0;
	if (only_wspace(line))
		return (-1);
	temp = rem_wspace(line);
	if (redirect_pipe_first(temp))
		return (-1);
	while (line[++i])
	{
		if ((line[i] == '"' || line[i] == '\'') && line[i] == line[i + 1])
		{
			line[i] = ' ';
			line[i + 1] = ' ';
		}
		else if (line[i] == '"' || line[i] == '\'')
			quote = quote_test(i, quote, line);
	}
	if (pipe_end_line_test(temp) && quote == 0)
		quote = '|';
	if (unexpected_token_test(temp) == false)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	if (first_test == true)
		return (quote_pipe_check(line, false));
	return (quote);
}
