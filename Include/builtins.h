/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:04:41 by tom               #+#    #+#             */
/*   Updated: 2024/08/13 18:55:04 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H


/**
 * @brief This function print every arguments ('arg') and return a buffer with
 * what is displayed.
 * 
 * @param arg The arguments that will be displayed.
 * @return char* buffer with what is displayed.
 */
char			*ft_echo(char **arg);

/**
 * @brief This function print the working directory.
 * 
 * @param arg The argument of the function (pwd takes no arguments).
 * @return bool This function returns whether the function succeeded or not.
 */
void			ft_pwd(t_ast **ast);

/**
 * @brief This function changes the current working directory of the calling
 * process to the directory specified in path.
 * 
 * @param arg The arguments that are given to the function.
 * @return true The working directory has changed correctly.
 * @return false The working directory has not changed correctly.
 */
bool			ft_cd(char **arg);

#endif