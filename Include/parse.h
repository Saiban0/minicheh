/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:06:37 by tom               #+#    #+#             */
/*   Updated: 2024/12/09 15:54:13 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

int				count_tab_size(char *command);
void			env_var_handler(t_ast **ast, t_env **env_start, int i);
int				*result_quote_tab(const char *str, int *res);

int				quote_pipe_check(char	*line);
void			open_quote(char	*text, t_ast	**ast, t_env	*env,
					char	*oldline);
bool			open_quote_pipe_test(char	*line, t_ast **ast, t_env *env);

/******************************************************************************/
/*                                                                            */
/* Open_quote_pipe_handler                                                    */
/*                                                                            */
/******************************************************************************/

char			**ft_split_arg(char *str);
char			*cuted(char const *str, int end);
int				result_length(char const *str);
bool			select_operator(char *line, int i, t_ast **ast);

/******************************************************************************/
/*                                                                            */
/* Parse_Utils                                                                */
/*                                                                            */
/******************************************************************************/

/**
 * @brief This function return whether the string contain only white space
 * or not.
 * 
 * @param str The string.
 * @return true The string contain only white space.
 * @return false The string not contain only white space.
 */
bool			only_wspace(char *str);

/**
 * @brief This function return 'c' if 'quote' equal 0, return 0 if 'quote'
 * equal 'c' and return 'quote' if 'quote' different from 'c' and 0.
 * 
 * @param c The char to test.
 * @param quote The result of the previous quote_test.
 * @return int An int.
 */
int				quote_test(char c, int quote);

/**
 * @brief This function search the environnement variable 'var' in 'envv'.
 * 
 * @param var The varible to find.
 * @param envv The environnement variable table.
 * @return char* The environnement variable to find or an empty string.
 */
char			*find_env_var(char	*var, char	**envv);

/**
 * @brief This function remove each white space before and after the command.
 * 
 * @param command The command.
 * @return char* The command whithout white space around it.
 */
char			*rem_wspace(char *command);

/******************************************************************************/
/*                                                                            */
/* Parse                                                                      */
/*                                                                            */
/******************************************************************************/

/**
 * @brief This function is the main function of the parse.
 * She read the command line and redirect to the right function.
 * 
 * @param line The command line.
 * @param ast The ast.
 * @param env_start A struct that contains the basic environment variables.
 * @return t_ast* The ast that is returned.
 */
void			parse(char *line, t_ast	**ast, t_env	*env_start, int quote);

/******************************************************************************/
/*                                                                            */
/* Parsing_Test                                                               */
/*                                                                            */
/******************************************************************************/

bool			open_quote_pipe_test(char	*line, t_ast **ast, t_env *env);

/**
 * @brief This function return whether 'c' is an operator or not.
 * 
 * @param c A char.
 * @return true The char is an operator.
 * @return false The char is not an operator.
 */
bool			is_op(char c);

/**
 * @brief This function return whether 'c' is a white space or not.
 * 
 * @param c A char.
 * @return true The char is a white space.
 * @return false The char is not a white space.
 */
bool			is_whitespace(char c);

/**
 * @brief This function return an struct who contain the command's type.
 * 
 * @param command The funtion ( first call of the command line ).
 * @return t_cmd_and_op An enum with the command's type.
 */
t_cmd_and_op	is_builtins(char *command);

/******************************************************************************/
/*                                                                            */
/* Pipe_Handler                                                               */
/*                                                                            */
/******************************************************************************/

/**
 * @brief This function handle the pipe in the command line.
 * 
 * @param line The command line.
 * @param i The position of the next pipe.
 * @param ast The ast that is returned in the parse function.
 */
void			ast_pipe(char *line, int i, t_ast **ast);

/******************************************************************************/
/*                                                                            */
/* Redirect_Handler                                                           */
/*                                                                            */
/******************************************************************************/

/**
 * @brief This function handle the redirect output ('>') in the command line.
 * 
 * @param line The command line
 * @param i The position of '>'.
 * @param ast The ast that is returned in the parse function.
 */
void			ast_else(char *line, int i, t_ast **ast, t_cmd_and_op op);

#endif