/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:33:43 by tom               #+#    #+#             */
/*   Updated: 2024/10/11 12:04:20 by tom              ###   ########.fr       */
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
	new_node->base->cmd_op = op;
	new_node->base->is_op = true;
	new_node->left = NULL;
	if (op == e_here_doc)
	{
		if (command)
			new_node->right->base->cmd = ft_split(command, ' ');
	}
	else if (op == e_redirect_input || op == e_redirect_output
		|| op == e_redirect_output_write_mod)
	{
		new_node->right->base->file_name = ft_strdup(command);
		new_node->right->base->cmd_op = e_file_name;
	}
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
	node = node->right;
}
