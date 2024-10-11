/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:44:47 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/11 12:37:11 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

/**
 * @brief Supplementary struct for the executing.
 * 
 */
typedef struct s_pipex
{
	int		pipe_i;
	char	*in_file;
	char	*out_file;
	int		(*pipe_fd)[2];
	int		status;
}				t_pipex;

/**
 * @brief This is the starting point of the executing part of the shell, it
 * allocates and initializes the pipex struct and starts the executing process.
 * 
 * @param cmd The starting point of the ast
 * @param env The env struct initialized in main
 */
void	exec_switch(t_ast *cmd, t_env *env);
/**
 * @brief This function is called upon executing a simple command (only one
 * command, no pipes or redirects)
 * 
 * @param cmd The ast base
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	exec_simple(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called upon executing a simple command that has 
 * redirects
 * 
 * @param cmd The ast base
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	exec_simple_redirect(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called upon executing a command pipeline, it is
 * recursive and will start executing the last (furthest to the right) command
 * first. It firsts uses the ft_getpath function to extract the command's path
 * and then child_execution to execute it.
 * 
 * @param cmd The ast base
 * @param pipex The pipex struct initialized in exec_switch
 * * @param env The env struct initialized in main
 */
void	exec_handle_pipe(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief Despite its name this function does not call upon a hitman to murder
 * children, instead it checks the postion of a given command in the ast,
 * creates a fork for them and calls upon the correct function to execute them.
 * 
 * @param cur_cmd Determines the current command and the behavior adopted by the
 *  function
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	child_execution(int cur_cmd, t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function executes a command if it is the last of the ast, it
 * redirects the output to stdout or a file if one has been provided in the ast.
 * 
 * @param cur_cmd Determines the current command and the behavior adopted by the
 *  function
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	last_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function executes a command if it is neither the last or the
 * first in the ast, the input and outputs follow the regular pipeline.
 * 
 * @param cur_cmd Determines the current command and the behavior adopted by the
 *  function
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	middle_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function executes a command if it is the first of the ast, it
 * redirects the input to stdin or a file if one has been provided in the ast.
 * 
 * @param cur_cmd Determines the current command and the behavior adopted by the
 *  function
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	first_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called upon every command execution, it uses getenv
 * to extract the PATH environment variable and uses ft_split and ft_strjoin to
 * return the found path of the command in a char *.
 * 
 * @param cmd The command name
 * @return char* The command path if found, else simply the command name.
 */
char	*ft_getpath(char *cmd);
/**
 * @brief This function is called at the start of the executing process, it
 * initializes every variable of the pipex_init function by default in_file and
 * out_file are "/dev/stdin" and "/dev/stdout" respectively, this can be changed
 * if there is a redirection in the ast.
 * 
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	ft_pipex_init(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called regurarly throughout the execution process, it
 * closes both ends of every pipes in the pipex->pipe_fd
 * 
 * @param cmd The current command's ast
 * @param env The env struct initialized in main
 */
void	close_pipes(t_pipex *pipex, t_env *env);
/**
 * @brief This function is called at the end of the pipeline and is used to wait
 * upon the completion of every command.
 * 
 * @param cmd The ast base
 * @param status The current status of executing
 */
void	wait_execution(t_ast *cmd, int *status);
/**
 * @brief This is used to create a fork using the current command's pid variable
 * 
 * @param pipex The pipex struct initialized in exec_switch
 * @param cmd The current command's ast
 */
void	create_fork(t_pipex *pipex, t_ast *cmd);
/**
 * @brief This function is called at the beginning and the end of the pipeline,
 * it is used to handle the redirections, if there are none, it simply redirects
 * to stdin and stdout
 * 
 * @param file_name The redirection file name, use stdin and stdout for default
 * behaviour
 * @param read_or_write 0 for read 1 for write
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @return int The file's fd
 */
int		get_fd(char *file_name, bool read_or_write, t_ast *cmd, t_pipex *pipex);
/**
 * @brief This function is called just after ft_pipex_init and search through
 * the entire ast for redirection operaterators
 * 
 * @param ast The ast's base
 * @param pipex The pipex structure
 */
void	search_redirects(t_ast *ast, t_pipex *pipex);
/**
 * @brief This function is simply a switch to redirect to the correct builtin
 * function
 * 
 * @param cmd The cmd's ast
 * @param env The env structure
 */
void	exec_builtins(t_ast *cmd, t_env *env);

#endif