/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:33:43 by tom               #+#    #+#             */
/*   Updated: 2024/10/25 15:04:59 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_operator(t_ast	*node, char	*command, t_cmd_and_op op)
{
	t_ast	*new_node;

	new_node = ft_calloc(1, sizeof(t_ast));
	new_node->base = ft_calloc(1, sizeof(t_ast_content));
	new_node->right = ft_calloc(1, sizeof(t_ast));
	new_node->right->base = ft_calloc(1, sizeof(t_ast_content));
	new_node->left = NULL;
	new_node->base->cmd_op = op;
	new_node->base->is_op = true;
	new_node->base->builtins = false;
	new_node->right->base->cmd_op = e_file_name;
	new_node->right->base->builtins = false;
	new_node->right->base->file_name = ft_strdup(rem_wspace(command));
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
		(*ast)->base->cmd = ft_split_arg(command, ' ');
		(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
		(*ast)->base->builtins = ((*ast)->base->cmd_op >= e_echo);
		free(command);
	}
	while (node->right)
		node = node->right;
	line += i + 1;
	i = 0;
	while (line[i] && !is_op(line[i]))
		i++;
	command = ft_calloc(i + 2, sizeof(char));
	ft_strlcat(command, line, i + 1);
	add_new_operator(node, command, op);
	free(command);
}
