/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:13:38 by tom               #+#    #+#             */
/*   Updated: 2024/06/25 19:17:35 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_ast
{
	t_ast_content *base;
	struct s_ast *gauche;
	struct s_ast *droite;
}	t_ast;

typedef struct s_ast_content
{
	bool is_op;
	char *cmd_op;
	bool builtins;
	bool flags;
	char *file_name;
}	t_ast_content;
