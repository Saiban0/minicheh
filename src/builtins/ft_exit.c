/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:11 by tom               #+#    #+#             */
/*   Updated: 2024/10/18 13:48:30 by tom              ###   ########.fr       */
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
			{
				ft_free_double_array(node->base->cmd);
				node->base->cmd = NULL;
			}
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
		node = NULL;
	}
}

void	ft_exit(char *line, t_ast *ast, t_env *env, t_pipex *pipex)
{
	if (ast)
		free_ast(pipex->ast_origin);
	if (pipex)
	{
		if (pipex->pipe_fd)
			free(pipex->pipe_fd);
		free(pipex);
		pipex = NULL;
	}
	if (line)
		free(line);
	if (env)
	{
		if (env->envv)
			ft_free_double_array(env->envv);
		if (env->oldpwd)
			free(env->oldpwd);
		if (env->pwd)
			free(env->pwd);

		free(env);
	}
	exit(0);
}
