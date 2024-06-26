/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:34:23 by tom               #+#    #+#             */
/*   Updated: 2024/06/28 18:36:08 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_base(char	*command, char	*line, t_ast	**ast, int	*operator)
{
	char	*tmp;
	
	tmp = ft_calloc(operator[0] + 2, sizeof(char));
	ft_strlcat(command, line, operator[1]);
	ft_strlcat(tmp, line, operator[0] + 1);
	tmp = rem_wspace(tmp);
	(*ast)->base->cmd_op = e_pipe;
	(*ast)->base->is_op = true;
	(*ast)->left = malloc(sizeof(t_ast *));
	(*ast)->left->base = malloc(sizeof(t_ast_content *));
	(*ast)->left->base->cmd = ft_split(tmp, ' ');
	(*ast)->left->base->cmd_op = is_builtins((*ast)->left->base->cmd[0]);
	free(tmp);
}

void	add_new_pipe_head(t_ast	**ast)
{
	t_ast	*new_head;
	
	new_head = malloc(sizeof(t_ast *));
	new_head->base = malloc(sizeof(t_ast_content *));
	new_head->base->cmd_op = e_pipe;
	new_head->base->is_op = true;
	new_head->left = *ast;
	new_head->right = NULL;
	(*ast) = new_head;
}

void	ast_pipe(char	*line, int	i, t_ast	**ast)
{
	char	*command;
	int		operator[2];
	char	*tmp;

	operator[0] = i;
	operator[1] = i + 1;
	while (line[operator[1]] && !is_op(line[operator[1]]))
		operator[1]++;
	command = ft_calloc(operator[1] + 1, sizeof(char));
	if ((*ast)->base->cmd_op == e_empty)
		first_base(command, line, ast, operator);
	else
		add_new_pipe_head(ast);
	line += i + 1;
	tmp = ft_calloc(operator[1] - i + 1, sizeof(char));
	ft_strlcat(tmp, line, operator[1] - i);
	(*ast)->right = malloc(sizeof(t_ast *));
	(*ast)->right->base = malloc(sizeof(t_ast_content *));
	(*ast)->right->base->cmd = ft_split(tmp, ' ');
	(*ast)->right->base->cmd_op = is_builtins((*ast)->right->base->cmd[0]);
	free(command);
	free(tmp);
}
