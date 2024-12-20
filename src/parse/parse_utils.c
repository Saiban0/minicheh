/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:08 by tom               #+#    #+#             */
/*   Updated: 2024/11/20 17:33:07 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	quote_test(char c, int quote)
{
	if (quote == 0)
		return (c);
	else if (quote == c)
		return (0);
	if (quote != 0 && c != quote)
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
	while (line[j] && is_whitespace(line[j]) == true)
		j++;
	if (!line[j])
		return (false);
	if (line[i] == '|' && line[i + 1] == '|')
		ft_exit(line, *ast, *(*ast)->t_env, NULL);
	else if (line[i] == '|')
		ast_pipe(line, i, ast);
	else if (line[i] == '<' && line[i + 1] == '<')
		ast_else(line, i + 1, ast, e_here_doc);
	else if (line[i] == '>' && line[i + 1] == '>')
		ast_else(line, i + 1, ast, e_redirect_output_write_mod);
	else if (line[i] == '>')
		ast_else(line, i, ast, e_redirect_output);
	else if (line[i] == '<')
		ast_else(line, i, ast, e_redirect_input);
	return (true);
}

char	*find_env_var(char	*var, char	**envv)
{
	int	i;
	int	var_size;

	i = -1;
	var_size = ft_strlen(var);
	while (envv[++i])
	{
		if (ft_strncmp(var, envv[i], var_size - 1) == 0)
			return (ft_strdup(envv[i] + var_size + 1));
	}
	return (ft_strdup(" "));
}
