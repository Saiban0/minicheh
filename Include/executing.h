/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:44:47 by bchedru           #+#    #+#             */
/*   Updated: 2024/12/16 19:59:52 by bchedru          ###   ########.fr       */
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
	int		in_fd;
	int		out_fd;
	int		pipe_fd[2][2];
	int		status;
	t_ast	*ast_origin;
}				t_pipex;

/**
 * @brief This is the starting point of the executing part of the shell, it
 * allocates and initializes the pipex struct, start the executing process and 
 * calls error_management after the executing is done.
 * 
 * @param cmd The starting point of the ast
 * @param env The env struct initialized in main
 */
int		exec_switch(t_ast *cmd, t_env *env);
/**
 * @brief This function is called upon executing a single command. It forks the
 * process if we are not executing an exception (cd, export or unset), then 
 * search for redirects through search_redirects and if it has found some, calls
 * exec_simple_redirect, else calls exec_only_child. The parent process simply 
 * waits with waitpid.
 * 
 * @param cmd The ast base
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	exec_simple(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called upon executing a single command that has 
 * redirects. It uses dup2 on pipex->in_fd and pipex->outfd, closes them then 
 * calls exec_only_child just like you would without redirections.
 * 
 * @param cmd The ast base
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	exec_simple_redirect(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called upon executing a command pipeline, it is
 * recursive and will start executing the last (furthest to the right) command
 * first. Every time it encounters a command node (Builtin or external command)
 * it increases pipex->pipe_i to allow the correct execution, and the process 
 * continues in child_execution.
 * 
 * @param cmd The ast base
 * @param pipex The pipex struct initialized in exec_switch
 * * @param env The env struct initialized in main
 */
void	exec_handle_pipe(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief Small function to prepare the start the execution process of the 
 * current command. It calls create_fork, then the child process will proceed
 * to the correct dups according to where we are in the pipeline and then 
 * pipe_exec will do the rest of the work.
 * 
 * @param cur_cmd Determines the current command and the behavior adopted by the
 *  function
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	pipe_execution(int curr_cmd, t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief Despite its name this function does not call upon a hitman to murder
 * children, instead it will look for redirections in the current command's ast
 * and make the dups if one was found, After that, if the command is a builtin,
 * exec_builtins will handle the rest, if not it's a standard execve call.
 * 
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
void	child_execution(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called upon every command execution, it uses getenv
 * to extract the PATH environment variable and uses ft_split and ft_strjoin to
 * return the found path of the command in a char *.
 * 
 * @param cmd The command name
 * @param env The env struct initialized in main
 * @return char* The command path if found, else simply the command name.
 */
char	*ft_getpath(char *cmd, t_env *env);
/**
 * @brief This function is called at the start of the executing process, it
 * initializes every variable of the pipex_init function by default in_fd and
 * out_fd are set to -1, this can be changed if there is a redirection in the
 * ast. The pipe_fd list is only initialized if there are more than one command
 * in the ast and when it is, only the correct number of pipes are created.
 * 
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env The env struct initialized in main
 */
int		ft_pipex_init(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called regurarly throughout the execution process, it
 * closes both ends of both pipes created in the pipex->pipe_fd
 * 
 * @param cmd The current command's ast
 */
void	close_pipes(t_pipex *pipex);
/**
 * @brief This is used to create a fork using the current command's pid variable
 * previously uninitialized.
 * 
 * @param pipex The pipex struct initialized in exec_switch
 * @param cmd The current command's ast
 */
void	create_fork(t_pipex *pipex, t_ast *cmd);
/**
 * @brief This function is called in search_redirect , it is used to handle the 
 * redirections, if there are none, it simply returns stdin or stdout.
 * The function will open the given file_name in read only, write only or append
 * write only depending on the given int and if it fails it calls
 * error_management.
 * 
 * @param file_name The redirection file name, use /dev/stdin and /dev/stdout 
 * for default behaviour
 * @param read_or_write 0 for read 1 for write 2 for append write
 * @param cmd The current command's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @return int The file's fd
 */
int		get_fd(char *file_name, int read_or_write, t_ast *cmd, t_pipex *pipex);
/**
 * @brief This function is called in every child executing processes and looks
 * recursively through every node to the right of the current one for redirects
 * (except for heredocs, it only looks to the first node to the right) and then
 * calls the appropraite function.
 * 
 * @param ast The ast's current node
 * @param pipex The pipex structure
 * @param env This is only used to avoid leaks when the user does a ctrl+c in
 * a heredoc
 */
void	search_redirects(t_ast *ast, t_pipex *pipex, t_env *env);
/**
 * @brief This simple function is called by search_redirects it checks if the
 * next right node is a redirect.
 * 
 * @param ast 
 * @return int 1 if next right node is a redirect, 0 if not
 */
int		check_redirect_type(t_ast *ast);
/**
 * @brief This function is called in search_redirects if an output redirect was
 * found, it will close any previously opened output redirection fd and open
 * a new one with the provided file name and in append mode if necessary.
 * 
 * @param ast The command's node
 * @param pipex The pipex structure
 * @param env This is only used to avoid leaks when the user does a ctrl+c in
 * a heredoc
 */
void	redirect_output_file(t_ast *ast, t_pipex *pipex, t_env *env);
/**
 * @brief This function is called in search_redirects if an input redirect was
 * found, it will close any previously opened input redirection fd and open
 * a new one with the provided file name.
 * 
 * @param ast The command's node
 * @param pipex The pipex structur
 * @param env This is only used to avoid leaks when the user does a ctrl+c in
 * a heredoc
 */
void	redirect_input_file(t_ast *ast, t_pipex *pipex, t_env *env);
/**
 * @brief This function is simply a switch to redirect to the correct builtin
 * function
 * 
 * @param cmd The cmd's ast
 * @param env The env structure
 * @param pipex the pipex structure
 */
void	exec_builtins(t_ast *cmd, t_env *env, t_pipex *pipex);
/**
 * @brief This function is called upon detection of a heredoc in a command and
 * starts the process of handling it. It will open a heredoc_tmp in the working
 * directory (supposed to change in the future), then use readline to open a 
 * prompt for the user to type the heredoc, closes it, then reopens it in read
 * only for the redirection to work properly down the line.
 * 
 * @param cmd The cmd's ast
 * @param pipex The pipex struct initialized in exec_switch
 * @param env This is only used to avoid leaks when the user does a ctrl+c
 */
void	handle_heredocs(t_ast *cmd, t_pipex *pipex, t_env *env);
/**
 * @brief This function is used to handle the ctrl+c signal in heredocs.
 * It simply closes the STDIN which causes the heredoc readline to stop.
 * Since heredocs should always be executed in a child, closing the stdin is not
 * a problem
 * 
 * @param signal a simple int that conveys signals
 */
void	heredoc_sigint_handler(int signal);
/**
 * @brief This function is called at the end of a pipeline execution it simply
 * uses waitpid to wait for the last command to be executed.
 * 
 * @param ast The ast's base
 */
void	wait_last_command(t_ast *ast);
/**
 * @brief This function simply copies the content of line inside the heredoc
 * file and frees it.
 * 
 * @param heredoc_fd The heredoc file's fd
 * @param line The line filled by readline
 */
void	heredoc_loop_cleanup(int heredoc_fd, char *line);
/**
 * @brief This function is called at the end of the heredoc function
 * It simply prepares the fd to be used properly in the execution of the command
 * 
 * @param heredoc_fd The heredoc file's fd
 * @param cmd The current command's ast
 * @param pipex The pipex struct
 */
void	heredoc_end(int heredoc_fd, t_ast *cmd, t_pipex *pipex);

#endif