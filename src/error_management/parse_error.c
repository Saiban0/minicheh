/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 16:30:37 by tom               #+#    #+#             */
/*   Updated: 2024/12/18 19:36:04 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

int	parse_error(int error_code, t_ast **ast, bool cmd_not_found)
{
	if (cmd_not_found)
		ft_putstr_fd("minishell: ", STDERR_FILENO);
	if (error_code == e_unexp_newline)
		ft_putstr_fd("syntax error near unexpected token `newline'\n",
			STDERR_FILENO);
	if (error_code == e_command_not_found)
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
	if (error_code == e_unexp_pipe)
		ft_putstr_fd("syntax error near unexpected token `|'\n",
			STDERR_FILENO);
	if (error_code == e_unexp_redir_input)
		ft_putstr_fd("syntax error near unexpected token `<'\n",
			STDERR_FILENO);
	if (error_code == e_unexp_redir_output)
		ft_putstr_fd("syntax error near unexpected token `>'\n",
			STDERR_FILENO);
	if (ast)
		free_ast(*ast);
	g_exit_code = 1;
	if (cmd_not_found)
		g_exit_code = CMDNOTFOUND;
	return (0);
}

bool	cmd_error(char *to_free)
{
	if (to_free)
		free(to_free);
	parse_error(e_command_not_found, NULL, false);
	return (false);
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
