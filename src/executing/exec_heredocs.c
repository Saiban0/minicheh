/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_heredocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:49:21 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/16 18:50:06 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_args(char **cmd, char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd[j])
		j++;
	while (args[i])
	{
		cmd[i + j] = ft_strdup(args[i]);
		i++;
	}
}

static void	add_to_tab(char *line, char **tab, char *delimiter)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	if (ft_strcmp(line, delimiter) != 0)
		tab[i] = line;
}

void	handle_heredocs(t_ast *cmd)
{
	char	*line;
	char	**heredoc_tab;

	line = get_next_line(STDIN_FILENO);
	heredoc_tab = NULL;
	add_to_tab(line, heredoc_tab, cmd->right->right->base->file_name);
	while (ft_strcmp(line, cmd->right->right->base->file_name) != 0)
	{
		line = get_next_line(STDIN_FILENO);
		add_to_tab(line, heredoc_tab, cmd->right->right->base->file_name);
	}
	add_args(cmd->base->cmd, heredoc_tab);
}
