/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:11 by tom               #+#    #+#             */
/*   Updated: 2024/10/17 16:53:06 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast	*node)
{
	if (node)
	{
		if (node->left)
			free_ast(node->left);
		if (node->right)
			free_ast(node->right);
		if (node->base)
		{
			if (node->base->cmd)
				ft_free_double_array(node->base->cmd);
			if (node->base->file_name)
			{
				free(node->base->file_name);
				node->base->file_name = NULL;
			}
			if (node->base->path)
				free(node->base->path);
			free(node->base);
		}
		free(node);
	}
}

void	ft_exit(char	*line, t_ast	*ast, t_env	*env)
{
	if (line)
		free(line);
	if (env)
	{
		if (env->envv)
			ft_free_double_array(env->envv);
		free(env);
	}
	if (ast)
		free_ast(ast);
	exit(0);
}
