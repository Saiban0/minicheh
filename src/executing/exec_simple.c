/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:54 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/25 20:07:05 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_simple(char *cmd, char **envp)
{
	char	**s_cmd;
	char	*path;

	if (cmd[0] == '\0')
		exit(0);
	s_cmd = ft_split(cmd, ' ');
	path = ft_getpath(s_cmd[0]);
	if (execve(path, s_cmd, envp) == -1)
	{
		ft_putstr_fd("minicheh: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_double_array(s_cmd);
		exit(0);
	}
}
