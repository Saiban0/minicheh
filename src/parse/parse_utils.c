/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:08 by tom               #+#    #+#             */
/*   Updated: 2024/12/11 17:30:32 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

char	*rem_wspace(char *command)
{
	int		i;
	int		j;
	int		z;
	char	*res;

	i = -1;
	j = -1;
	while (command[++i] && is_whitespace(command[i]))
		continue ;
	j = ft_strlen(command) - 1;
	while (command[j] && is_whitespace(command[j]))
		j--;
	res = ft_calloc(1, sizeof(char) * (j - i + 2));
	z = -1;
	while (command[i] && i <= j)
		res[++z] = command[i++];
	return (res);
}

int	quote_test(int i, int quote, char *line)
{
	if (quote == 0)
		return (line[i]);
	else if (quote == line[i])
		return (0);
	if (quote != 0 && line[i] != quote)
		return (quote);
	return (-1);
}

bool	only_wspace(char	*str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (!is_whitespace(str[i]))
			return (false);
	return (true);
}

bool	select_operator(char *line, int i, t_ast **ast)
{
	int	j;

	j = i + 1;
	if (!line[j])
		return (parse_error_handler(e_unexp_pipe, ast, false));
	while (line[j] && is_whitespace(line[j]) == true)
		j++;
	if (line[i] == '|' && line[i + 1] == '|')
		return (parse_error_handler(e_unexp_pipe, ast, false));
	else if (line[i] == '|')
		return (ast_pipe(line, i, ast, NULL));
	else if (line[i] == '<' && line[i + 1] == '<')
		return (ast_else(line, i + 1, ast, e_here_doc));
	else if (line[i] == '>' && line[i + 1] == '>')
		return (ast_else(line, i + 1, ast, e_redirect_output_write_mod));
	else if (line[i] == '>')
		return (ast_else(line, i, ast, e_redirect_output));
	else if (line[i] == '<')
		return (ast_else(line, i, ast, e_redirect_input));
	return (true);
}

char	*find_env_var(char	*var, char	**envv)
{
	int	i;
	int	var_size;

	i = -1;
	var += (var[0] == '$');
	if (var[0] == '?')
		return (ft_itoa(g_exit_code));
	var_size = ft_strlen(var);
	while (envv[++i])
	{
		if (ft_strncmp(var, envv[i], var_size - 1) == 0)
			return (ft_strdup(envv[i] + var_size + 1));
	}
	return (ft_strdup(" "));
}
