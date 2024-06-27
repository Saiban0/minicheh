/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:44:47 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/27 15:42:48 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

void	exec_switch(t_ast *cmd, char **envp);
void	exec_extern(t_ast *cmd, char **envp);
void	exec_child(t_ast *cmd, char **envp, char *cmd_path);
int		open_file(char *file, int in_or_out, t_ast *cmd);
int		check_dir(char *cmd);
char	*ft_getpath(char *cmd);

#endif