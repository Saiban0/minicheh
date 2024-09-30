/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:21:40 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/24 18:52:32 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H

typedef enum s_error_management
{
	e_none = 0,
	e_command_not_found = 1,
	e_file = 2,
	e_empty_command = 3,
	e_fork_failure = 4,
	e_pipe_failure = 5,
	e_env_error =6,
	e_malloc_failure = 7,
}	t_error;

void	error_management(int error_code, t_ast *cmd, t_pipex *pipex);
#endif