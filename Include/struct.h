/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:13:38 by tom               #+#    #+#             */
/*   Updated: 2024/10/01 18:24:43 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

/**
 * @brief This struct contain every builtins and operator 
 * handled by the minicheh :
 * - The function or operator not handled by the minicheh.:
 * - The operator '|'.
 * - The operator '<'.
 * - The operator '>'.
 * - The operator '<<'.
 * - The operator '>>'.
 * - The operator '$' followed by a sequence of characters.
 * - The operator '$?' should expand to the exit status of the most recently
 * executed foreground pipeline.
 * - bash's echo function.
 * - bash's cd function.
 * - bash's pwd function.
 * - bash's export function.
 * - bash's unset function.
 * - bash's exit function.
 * - bash's env function.
 */
typedef enum s_cmd_and_op
{
	e_empty,
	e_external_control,
	e_pipe,
	e_redirect_input,
	e_redirect_output,
	e_here_doc,
	e_redirect_output_write_mod,
	e_echo,
	e_cd,
	e_pwd,
	e_export,
	e_unset,
	e_exit,
	e_env
}	t_cmd_and_op;

typedef struct s_ast_content
{
	bool			is_op;
	t_cmd_and_op	cmd_op;
	char			**cmd;
	bool			builtins;
	char			*file_name;
	char			*path;
	pid_t			pid;
}	t_ast_content;

typedef struct s_minishell_env
{
	char			*pwd;
	int				nb_commands;
	char			**envv;
}	t_env;

typedef struct s_ast
{
	t_env			**t_env;
	t_ast_content	*base;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;

#endif