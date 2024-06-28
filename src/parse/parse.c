/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/06/28 18:37:01 by tom              ###   ########.fr       */
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

t_ast	*parse(char *line)
{
	t_ast	*ast;
	int		i;

	i = -1;
	ast = malloc(sizeof(t_ast *));
	ast->base = malloc(sizeof(t_ast_content *));
	ast->base->cmd_op = e_empty;
	ast->left = NULL;
	ast->right = NULL;
	while (line[++i])
	{
		if (is_op(line[i]))
		{
			if (line[i] == '|')
				ast_pipe(line, i, &ast);
			if (line[i] == '>')
				ast_redirect_output(line, i, &ast);
			line += i;
			i = 0;
		}
	}
	return (ast);
}
