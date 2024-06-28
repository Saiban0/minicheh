/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:06:37 by tom               #+#    #+#             */
/*   Updated: 2024/06/28 02:59:47 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_ast	*parse(char *line);

/**
 * @brief This function handle the pipe of the commande line and put it in
 * the strcut ast ( abstract syntax tree ).
 * 
 * @param line The commande line.
 * @param i The positions of the first pipe ('|').
 * @param ast The ast.
 */
void	ast_pipe(char	*line, int	i, t_ast	**ast);

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
