/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:04:41 by tom               #+#    #+#             */
/*   Updated: 2024/10/15 17:44:46 by tom              ###   ########.fr       */
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
void			ft_echo(char **arg);

void			ft_env(char **arg, t_env	*env);

void			free_ast(t_ast	*node);
void			ft_exit(char	*line, t_ast	*ast, t_env	*env);

bool			ft_cd(char	**arg, t_env	**env);

void			ft_pwd(char	**arg, t_env	*env);

bool			check_arg(char	*arg, t_env	**env);
char			**double_array_cat(char	**tab1, char	**tab2);
bool			ft_find(char	*arg, t_env	**env, char	**to_find);
void			ft_export(char	**arg, t_env	**env);


#endif