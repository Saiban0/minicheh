/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:06:37 by tom               #+#    #+#             */
/*   Updated: 2024/07/26 10:57:50 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/******************************************************************************/
/*                                                                            */
/* Parse_Utils                                                                */
/*                                                                            */
/******************************************************************************/

/**
 * @brief This function remove each white space before and after the command.
 * 
 * @param command The command.
 * @return char* The command whithout white space around it.
 */
char	*rem_wspace(char *command);

/******************************************************************************/
/*                                                                            */
/* Parse                                                                      */
/*                                                                            */
/******************************************************************************/

t_cmd_and_op	is_builtins(char *command);
/**
 * @brief This function is the main function of the parse.
 * She read the command line and redirect to the right function.
 * 
 * @param line The command line.
 * @param ast The ast.
 * @param env_start A struct that contains the basic environment variables.
 * @return t_ast* The ast that is returned.
 */
void	parse(char *line, t_ast	**ast, t_env	*env_start);

/******************************************************************************/
/*                                                                            */
/* Parsing_Test                                                               */
/*                                                                            */
/******************************************************************************/

/**
 * @brief This function return whether 'c' is an operator or not.
 * 
 * @param c A char.
 * @return true The char is an operator.
 * @return false The char is not an operator.
 */
bool	is_op(char	c);

/**
 * @brief This function return whether 'c' is a white space or not.
 * 
 * @param c A char.
 * @return true The char is a white space.
 * @return false The char is not a white space.
 */
bool	is_whitespace(char	c);

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
void	ast_pipe(char	*line, int	i, t_ast	**ast);

/******************************************************************************/
/*                                                                            */
/* Redirect_Handler                                                    */
/*                                                                            */
/******************************************************************************/

/**
 * @brief This function handle the redirect output ('>') in the command line.
 * 
 * @param line The command line
 * @param i The position of '>'.
 * @param ast The ast that is returned in the parse function.
 */
void	ast_else(char	*line, int	i, t_ast	**ast, t_cmd_and_op op);

#endif