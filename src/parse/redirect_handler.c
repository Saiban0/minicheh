/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:33:43 by tom               #+#    #+#             */
/*   Updated: 2024/07/10 08:50:52 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_operator(t_ast	*node, char	*right_cmd, t_cmd_and_op op)
{
	t_ast	*new_node;

	new_node = malloc(sizeof(t_ast *));
	new_node->base = malloc(sizeof(t_ast_content *));
	new_node->right = malloc(sizeof(t_ast *));
	new_node->right->base = malloc(sizeof(t_ast_content *));
	new_node->base->cmd_op = op;
	new_node->base->is_op = true;
	new_node->left = NULL;
	new_node->right->base->cmd = ft_split(right_cmd, ' ');
	new_node->right->base->cmd_op = is_builtins(new_node->right->base->cmd[0]);
	node->right = new_node;
}

void	ast_else(char	*line, int	i, t_ast	**ast, t_cmd_and_op	op)
{
	char	*command;
	t_ast	*node;

	node = *ast;
	if (node->base->cmd_op == e_empty)
	{
		command = ft_calloc(i + 1, sizeof(char));
		ft_strlcat(command, line, i);
		(*ast)->base->cmd = ft_split(command, ' ');
		(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
		free(command);
	}
	while (node->right)
		node = node->right;
	line += i + 1;
	i = 0;
	while (line[i] && !is_op(line[i]))
		i++;
	command = ft_calloc(i + 1, sizeof(char));
	ft_strlcat(command, line, i);
	add_new_operator(node, command, op);
	node = node->right;
}
