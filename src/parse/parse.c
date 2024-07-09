/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/07/09 11:59:26 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	last_command(char *line, t_ast	**ast)
{
	(*ast)->base->cmd = ft_split(line, ' ');
	(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
}

void	parse(char *line, t_ast	**ast)
{
	int		i;

	i = -1;
	(*ast) = malloc(sizeof(t_ast *));
	(*ast)->base = malloc(sizeof(t_ast_content *));
	(*ast)->base->cmd_op = e_empty;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	while (line[++i])
	{
		if (is_op(line[i]))
		{
			if (line[i] == '<' && line[i + 1] == '<')
				ast_redirect(line, i + 1, ast, e_here_doc);
			else if (line[i] == '>' && line[i + 1] == '>')
				ast_redirect(line, i + 1, ast, e_redirect_output_write_mod);
			else if (line[i] == '|')
				ast_pipe(line, i, ast);
			else if (line[i] == '>')
				ast_redirect(line, i, ast, e_redirect_output);
			else if (line[i] == '<')
				ast_redirect(line, i, ast, e_redirect_input);
			line += i;
			i = 0;
		}
	}
	if ((*ast)->base->cmd_op == e_empty)
		last_command(line, ast);
}
