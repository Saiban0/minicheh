/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/08/04 13:16:15 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	last_command(char *line, t_ast	**ast)
{
	(*ast)->base->cmd = ft_split(line, ' ');
	(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
}

void	select_operator(char	*line, int	i, t_ast	**ast)
{
	if (line[i] == '|')
		ast_pipe(line, i, ast);
	else if (line[i] == '<' && line[i + 1] == '<')
		ast_else(line, i + 1, ast, e_here_doc);
	else if (line[i] == '>' && line[i + 1] == '>')
		ast_else(line, i + 1, ast, e_redirect_output_write_mod);
	else if (line[i] == '>')
		ast_else(line, i, ast, e_redirect_output);
	else if (line[i] == '<')
		ast_else(line, i, ast, e_redirect_input);
}

void		add_env(t_env	**env_start, t_ast	**ast)
{
	(*env_start)->ast_size += (*ast)->base->cmd_op != e_empty;
	(*ast)->t_env = env_start;
	if ((*ast)->left)
		add_env(env_start, &(*ast)->left);
	if ((*ast)->right)
		add_env(env_start, &(*ast)->right);
}

void	parse(char *line, t_ast	**ast, t_env	*env_start)
{
	int		i;

	i = -1;
	(*ast)->base->cmd_op = e_empty;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	(*ast)->t_env = NULL;
	while (line[++i])
	{
		if (is_op(line[i]))
		{
			select_operator(line, i, ast);
			line += i;
			i = 0;
		}
	}
	if ((*ast)->base->cmd_op == e_empty)
		last_command(line, ast);
	env_start->ast_size = 0;
	add_env(&env_start, ast);
}
