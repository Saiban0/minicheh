/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quote_pipe_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:25:23 by tom               #+#    #+#             */
/*   Updated: 2024/11/18 15:15:33 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_between_op(char *temp, int i)
{
	while (temp[--i] && is_whitespace(temp[i]))
		continue ;
	if (temp[i] == '|' || temp[i] == '<' || temp[i] == '>')
		return (false);
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
	if (temp[0] == '|')
	{
		parse_error_handler(e_unexpected_pipe, NULL);
		free(temp);
		return (-1);
	}
	while (temp[++i])
		if (temp[i] == '"' || temp[i] == '\'')
			quote = quote_test(temp[i], quote);
	if (temp[i - 1] == '|')
		quote = '|';
	if (temp[i - 1] == '|' || temp[i - 1] == '<' || temp[i - 1] == '>')
	{
		if (check_between_op(temp, i) == false)
		{
			parse_error_handler(e_unexpected_pipe, NULL);
			free(temp);
			return (-1);
		}
	}
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

bool	open_quote_pipe_test(char	*line, t_ast **ast, t_env *env)
{
	int		quote_pipe_res;

	quote_pipe_res = quote_pipe_check(line);
	if (quote_pipe_res == 0)
		return (true);
	if (quote_pipe_res == -1)
		return (false);
	else if (quote_pipe_res == '|')
		open_quote("pipe> ", ast, env, line);
	else if (quote_pipe_res == '"')
		open_quote("dquote> ", ast, env, line);
	else if (quote_pipe_res == '\'')
		open_quote("quote> ", ast, env, line);
	return (false);
}
