/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:30:37 by tom               #+#    #+#             */
/*   Updated: 2024/11/15 16:38:13 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse_error_handler(int error_code, t_ast **ast)
{
	if (error_code == e_unexpected_newline)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
	}
	(*ast)->base->cmd_op = e_empty;
	return ;
}
