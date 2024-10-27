/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 09:04:41 by tom               #+#    #+#             */
/*   Updated: 2024/10/23 15:51:57 by bchedru          ###   ########.fr       */
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
void			ft_echo(char **arg, t_ast *cmd, t_env *env, t_pipex *pipex);

void			ft_env(char **arg, t_env *env, t_ast *cmd, t_pipex *pipex);

void			free_ast(t_ast *node);
void			ft_exit(char *line, t_ast *ast, t_env *env, t_pipex *pipex);

bool			ft_cd(char **arg, t_env **env);

void			ft_pwd(char **arg, t_env *env, t_ast *ast, t_pipex *pipex);

/**
 * @brief Return whether the string contain a special character or not.
 * 
 * @param str The string.
 * @return true The string contain a special character.
 * @return false The string not contain a special character.
 */
bool			check_special_char(char *str);
bool			check_export_arg(char *arg, t_env **env);
char			**double_array_cat(char **tab1, char **tab2);
bool			ft_find_export(char *arg, t_env **env, char **to_find);
void			ft_export(char **arg, t_env **env);

void			ft_unset(char **arg, t_env **env);

#endif