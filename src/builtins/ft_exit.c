/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:02:11 by tom               #+#    #+#             */
/*   Updated: 2024/10/10 14:03:56 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_ast(t_ast	*node)
{
	if (node->left)
		free_ast(node->left);
	if (node->right)
		free_ast(node->right);
	if (node->base)
	{
		ft_free_double_array(node->base->cmd);
		free(node->base);
	}
	free(node);
}

void	ft_exit(char	*line, t_ast	**ast, t_env	*env)
{
	free(line);
	ft_free_double_array(env->envv);
	free(env->pwd);
	free(env);
	free_ast(*ast);
	exit(0);
}
