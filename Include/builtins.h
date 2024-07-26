/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:04:41 by tom               #+#    #+#             */
/*   Updated: 2024/07/12 18:10:20 by tom              ###   ########.fr       */
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

#endif