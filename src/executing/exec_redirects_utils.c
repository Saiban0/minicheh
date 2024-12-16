/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 19:55:57 by bchedru           #+#    #+#             */
/*   Updated: 2024/12/16 20:00:00 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_end(int heredoc_fd, t_ast *cmd, t_pipex *pipex)
{
	close(heredoc_fd);
	pipex->in_fd = open("/tmp/heredoc_tmp", O_RDONLY);
	if (pipex->in_fd == -1)
		error_management(e_file_name, cmd, pipex, NULL);
}

void	heredoc_loop_cleanup(int heredoc_fd, char *line)
{
	ft_putstr_fd(line, heredoc_fd);
	ft_putstr_fd("\n", heredoc_fd);
	free(line);
}
