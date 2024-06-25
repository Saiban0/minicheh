/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:44:47 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/25 20:06:35 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

void	exec_simple(char *cmd, char **envp);
int		open_file(char *file, int in_or_out);
int		check_dir(char *cmd);
char	*ft_getpath(char *cmd);

#endif