/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:21:40 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/25 21:59:33 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H

#include "minishell.h"

typedef enum s_error_management
{
	e_command_not_found
}	t_error;

void	error_management(int error_code, t_ast *cmd);

#endif