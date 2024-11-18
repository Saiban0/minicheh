/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 17:34:23 by tom               #+#    #+#             */
/*   Updated: 2024/11/18 14:46:22 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	first_base( char	*line, t_ast	**ast, int	*operator)
{
	char	*temp;
	char	*temp_bis;

	temp = ft_calloc(operator[0] + 1, sizeof(char));
	ft_strlcat(temp, line, operator[0]);
	temp_bis = rem_wspace(temp);
	free(temp);
	(*ast)->base->cmd_op = e_pipe;
	(*ast)->base->is_op = true;
	(*ast)->left = ft_calloc(1, sizeof(t_ast));
	(*ast)->left->base = ft_calloc(1, sizeof(t_ast_content));
	free(temp_bis);
	(*ast)->left->base->cmd = ft_split_arg(temp_bis, ' ');
	(*ast)->left->base->cmd_op = is_builtins((*ast)->left->base->cmd[0]);
	(*ast)->left->base->builtins = ((*ast)->left->base->cmd_op >= e_echo);
}

void	add_new_pipe_head(t_ast	**ast)
{
	t_ast	*new_head;

	new_head = malloc(sizeof(t_ast));
	new_head->base = malloc(sizeof(t_ast_content));
	new_head->left = *ast;
	new_head->right = NULL;
	new_head->base->is_op = true;
	new_head->base->cmd_op = e_pipe;
	new_head->base->builtins = false;
	(*ast) = new_head;
}

void	ast_pipe(char *line, int i, t_ast **ast)
{
	int		operator[2];
	char	*tmp;

	operator[0] = i;
	operator[1] = i + 1;
	while (line[operator[1]] && !is_op(line[operator[1]]))
		operator[1]++;
	if ((*ast)->base->cmd_op == e_empty)
		first_base(line, ast, operator);
	else
		add_new_pipe_head(ast);
	line += i + 1;
	tmp = ft_calloc(operator[1] - i + 1, sizeof(char));
	ft_strlcat(tmp, line, operator[1] - i);
	(*ast)->right = ft_calloc(1, sizeof(t_ast));
	(*ast)->right->base = ft_calloc(1, sizeof(t_ast_content));
	(*ast)->right->base->cmd = ft_split_arg(tmp, ' ');
	(*ast)->right->base->cmd_op = is_builtins((*ast)->right->base->cmd[0]);
	(*ast)->right->base->builtins = ((*ast)->right->base->cmd_op >= e_echo);
	free(tmp);
}
