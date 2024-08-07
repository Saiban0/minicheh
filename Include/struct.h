/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:13:38 by tom               #+#    #+#             */
/*   Updated: 2024/07/09 11:49:16 by tom              ###   ########.fr       */
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
	bool			builtins;
	bool			flags;
	char			**cmd;
	char			*file_name;
}	t_ast_content;

typedef struct s_ast
{
	t_ast_content	*base;
	struct s_ast	*left;
	struct s_ast	*right;
}	t_ast;


#endif