/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:21:40 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/18 15:22:28 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGEMENT_H
# define ERROR_MANAGEMENT_H

# define SYNTAX_ERROR 2
# define MALLOC_ERROR 12 //ENOMEM
# define BUILTIN_ERROR 42 //the builtin doesn't respect the subject
# define CMDNOTFOUND 127 //command doesn’t exist, or isn’t in $PATH.
# define EXIT_SIGINT 130 //SIGINT triggered closure
# define EXIT_SIGQUIT 131 //SIGQUIT triggered closure

typedef enum s_error_management
{
	e_none = 0,
	e_command_not_found = 1,
	e_file = 2,
	e_empty_command = 3,
	e_fork_failure = 4,
	e_pipe_failure = 5,
	e_env_error = 6,
	e_malloc_failure = 7,
	e_unexpected_newline = 8,
	e_too_many_arg = 9,
	e_no_such_file_or_dir = 10,
	e_unexpected_pipe = 11,
	e_unexpected_redirect_input = 12,
	e_unexpected_redirect_output = 13,
}	t_error;

/**
 * @brief This function is called upon every error case. It prints an error
 * message, frees every allocated memory then exits the program.
 * 
 * @param error_code The error code referring to the t_error enum
 * @param cmd The current command's ast
 * @param pipex The pipex structure initiliazed in exec_switch
 * @param env The env struct initialized in main.c is only used here with the
 * error codes 1 and 4 to call ft_exit
 */
void	error_management(int error_code, t_ast *cmd, t_pipex *pipex,
			t_env *env);
/**
 * @brief This function behaves very similarly to ft_exit, except it is called
 * more often than its counterpart because this one does not exit the process.
 * The function will check if every provided variable that can be allocated is 
 * allocated and frees them.
 * 
 * @param cmd The current command's ast
 * @param pipex The pipex structure initiliazed in exec_switch
 * @param env Only used to check th number of commands to avoid conditional 
 * jumps
 */
void	error_free(t_ast *cmd, t_pipex *pipex, t_env *env);

void	parse_error_handler(int error_code, t_ast **ast);

bool	cd_error(char *home, t_error error_code, char *file);

#endif