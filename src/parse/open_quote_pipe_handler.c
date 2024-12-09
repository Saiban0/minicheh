/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quote_pipe_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:25:23 by tom               #+#    #+#             */
/*   Updated: 2024/12/09 18:05:58 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpected_token_distrib(char *temp, int i, int op)
{
	if (temp[i] == '|' || temp[i] == '>' || temp[i] == '<')
	{
		if (op == 1)
		{
			if (temp[i] == '|')
				parse_error_handler(e_unexpected_pipe, NULL);
			if (temp[i] == '>')
				parse_error_handler(e_unexpected_redirect_output, NULL);
			if (temp[i] == '<')
				parse_error_handler(e_unexpected_redirect_input, NULL);
			free(temp);
			return (-1);
		}
		if ((temp[i] == '<' && temp[i + 1] == '<')
			|| (temp[i] == '>' && temp[i + 1] == '>'))
			i++;
		op = 1;
	}
	else if (is_whitespace(temp[i]) == false)
		op = 0;
	return (op);
}

bool	unexpected_token_test(int i, char *temp)
{
	int	op;

	op = 0;
	if ((temp[i - 1] == '<' && temp[i - 2] != '<') || temp[i - 1] == '>')
	{
		if (temp[i - 1] == '<' && temp[i - 2] != '<')
			parse_error_handler(e_unexpected_redirect_input, NULL);
		if (temp[i - 1] == '>')
			parse_error_handler(e_unexpected_redirect_output, NULL);
		free(temp);
		return (false);
	}
	i = -1;
	while (temp[++i])
	{
		op = unexpected_token_distrib(temp, i, op);
		if (op == -1)
			return (false);
	}
	return (true);
}

bool	redirect_pipe_first(char *temp)
{
	if (temp[0] == '|')
		parse_error_handler(e_unexpected_pipe, NULL);
	else if (temp[0] == '<')
		parse_error_handler(e_unexpected_redirect_input, NULL);
	else if (temp[0] == '>')
		parse_error_handler(e_unexpected_redirect_output, NULL);
	else
		return (false);
	free(temp);
	return (true);
}

int	quote_pipe_check(char	*line)
{
	int		i;
	int		quote;
	char	*temp;

	i = -1;
	quote = 0;
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
	if (line[i - 1] == '|' && quote == 0)
		quote = '|';
	if (unexpected_token_test(i, line) == false)
		return (-1);
	free(temp);
	return (quote);
}

void	open_quote(char	*text, t_ast	**ast, t_env	*env, char	*oldline)
{
	char	*newline;
	char	*temp;

	temp = readline(text);
	newline = ft_calloc(ft_strlen(temp) + ft_strlen(oldline) + 2, sizeof(char));
	ft_strlcat(newline, oldline, ft_strlen(temp) + ft_strlen(oldline) + 1);
	ft_strlcat(newline, temp, ft_strlen(temp) + ft_strlen(oldline) + 1);
	parse(newline, ast, env, 0);
	free(newline);
}
