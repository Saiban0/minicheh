/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:30:37 by tom               #+#    #+#             */
/*   Updated: 2024/11/12 14:19:39 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error_handler(int	error_code, t_ast	**ast)
{
	if (error_code == e_unexpected_newline)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
	}
	(*ast)->base->cmd_op = e_empty;
	return ;
}
