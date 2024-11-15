/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:30:37 by tom               #+#    #+#             */
/*   Updated: 2024/11/15 17:47:49 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	parse_error_handler(int	error_code, t_ast	**ast)
{
	if (error_code == e_unexpected_newline)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
						STDERR_FILENO);
	}
	(*ast)->base->cmd_op = e_empty;
	g_exit_code = 1;
	return ;
}

bool	cd_error(char *home, t_error error_code, char *file)
{
	if (error_code == e_no_such_file_or_dir)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(file, STDERR_FILENO);
		ft_putstr_fd(": no such file or directory:\n", STDERR_FILENO);
	}
	else if (error_code == e_too_many_arg)
		ft_putstr_fd("minicheh: cd: too many arguments\n", STDERR_FILENO);
	if (home)
		free(home);
	g_exit_code = 1;
	return (false);
}
