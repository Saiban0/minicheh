/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:49:21 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/21 21:07:32 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_heredocs(t_ast *cmd, t_pipex *pipex)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		error_management(e_file_name, cmd, pipex);
	while (true)
	{
		line = readline("heredoc> ");
		if (ft_strcmp(line, cmd->right->right->base->file_name) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, heredoc_fd);
		ft_putstr_fd("\n", heredoc_fd);
		free(line);
	}
	close(heredoc_fd);
	pipex->in_fd = open("heredoc_fd", O_RDONLY);
	if (heredoc_fd == -1)
		error_management(e_file_name, cmd, pipex);
}
