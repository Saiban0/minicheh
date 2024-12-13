/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quote_pipe_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:25:23 by tom               #+#    #+#             */
/*   Updated: 2024/12/13 14:01:36 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_redirect_test(int i, char *temp)
{
	if (temp[i] == '<' && temp[i + 1] == '>')
		return (parse_error_handler(e_unexp_redir_output, NULL, false) - 1);
	else if (temp[i] == '>' && temp[i + 1] == '<')
		return (parse_error_handler(e_unexp_redir_input, NULL, false) - 1);
	else if (temp[i] == temp[i + 1] && temp[i - 1] == temp[i])
	{	
		if (temp[i] == '>')
			return (parse_error_handler(e_unexp_redir_output, NULL, false) - 1);
		if (temp[i] == '<')
			return (parse_error_handler(e_unexp_redir_input, NULL, false) - 1);
	}
	else if (temp[i] == temp[i + 1] && temp[i - 1] != temp[i])
		i++;
	return (i);
}

bool	unexpected_token_test(char *temp, int op)
{
	int	i;

	i = -1;
	while (temp[++i])
	{
		if (temp[i] == '|' || temp[i] == '>' || temp[i] == '<')
		{
			if (op > 0)
			{
				if (temp[i] == '|')
					return (parse_error_handler(e_unexp_pipe, NULL, false));
				if (temp[i] == '>')
					return (parse_error_handler(e_unexp_redir_output, NULL, false));
				if (temp[i] == '<')
					return (parse_error_handler(e_unexp_redir_input, NULL, false));
			}
			op = temp[i];
			if (op == '<' || op == '>')
				i = unexpected_redirect_test(i, temp);
			if (i == -1)
				return (false);
		}
		else if (!is_whitespace(temp[i]))
			op = 0;
	}
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
	else
		return (false);
	free(temp);
	return (true);
}

bool	op_end_line_test(char *line)
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
		return ('|');
	if (i == '<')
		return ('<');
	if (i == '>')
		return ('>');
	return (false);
}

int	quote_pipe_check(char	*line)
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
		if (line[i] == '"' || line[i] == '\'')
			quote = quote_test(i, quote, line);
	if (quote == 0)
		quote = op_end_line_test(line);
	if (unexpected_token_test(temp, 0) == false)
	{
		free(temp);
		return (-1);
	}
	free(temp);
	return (quote);
}
