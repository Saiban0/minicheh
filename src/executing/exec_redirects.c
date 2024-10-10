/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 13:52:05 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/10 16:47:08 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	search_redirects(t_ast *ast, t_pipex *pipex)
{
	if (ast->left)
		search_redirects(ast->left, pipex);
	if (ast->right)
		search_redirects(ast->right, pipex);
	if (ast->base->cmd_op == e_redirect_input && ast->left->base->file_name)
		pipex->in_file = ast->left->base->file_name;
	if (ast->base->cmd_op == e_redirect_output && ast->right->base->file_name)
		pipex->out_file = ast->right->base->file_name;
}
