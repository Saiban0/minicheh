/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:49:21 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/23 15:58:43 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_end(int heredoc_fd, t_ast *cmd, t_pipex *pipex)
{
	close(heredoc_fd);
	pipex->in_fd = open("heredoc_tmp", O_RDONLY);
	if (pipex->in_fd == -1)
		error_management(e_file_name, cmd, pipex, NULL);
}

void	handle_heredocs(t_ast *cmd, t_pipex *pipex)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open("heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		error_management(e_file_name, cmd, pipex, NULL);
	while (true)
	{
		line = readline("heredoc> ");
		if (line == NULL)
		{
			ft_putstr_fd("Heredoc received SIGINT during prompt\n",
				STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, cmd->right->right->base->file_name) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, heredoc_fd);
		ft_putstr_fd("\n", heredoc_fd);
		free(line);
	}
	heredoc_end(heredoc_fd, cmd, pipex);
}
