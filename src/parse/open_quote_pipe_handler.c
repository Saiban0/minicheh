/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quote_pipe_handler.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:25:23 by tom               #+#    #+#             */
/*   Updated: 2024/11/07 16:25:49 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_pipe_check(char	*line)
{
	int		i;
	int		quote;
	char	*temp;

	i = -1;
	quote = 0;
	temp = rem_wspace(line);
	while (temp[++i])
		if (temp[i] == '"' || temp[i] == '\'')
				quote = quote_test(temp[i], quote);
	if (temp[i - 1] == '|')
		quote = '|';
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

void	text_open_quote_select(char	*line, t_ast	**ast, t_env	*env, int	quote_pipe_res)
{
	if (quote_pipe_res == '|')
		open_quote("pipe> ", ast, env, line);
	else if (quote_pipe_res == '"')
		open_quote("dquote> ", ast, env, line);
	else if (quote_pipe_res == '\'')
		open_quote("quote> ", ast, env, line);
}
