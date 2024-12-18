/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:49:21 by bchedru           #+#    #+#             */
/*   Updated: 2024/12/16 19:55:34 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_input_file(t_ast *ast, t_pipex *pipex, t_env *env)
{
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	pipex->in_fd = get_fd(ast->right->base->file_name, 0, ast, pipex);
	if (ast->right->right)
		search_redirects(ast->right->right, pipex, env);
}

void	redirect_output_file(t_ast *ast, t_pipex *pipex, t_env *env)
{
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	if (ast->base->cmd_op == e_redirect_output)
		pipex->out_fd = get_fd(ast->right->base->file_name, 1, ast, pipex);
	if (ast->base->cmd_op == e_redirect_output_write_mod)
		pipex->out_fd = get_fd(ast->right->base->file_name, 2, ast, pipex);
	if (ast->right->right)
		search_redirects(ast->right->right, pipex, env);
}

void	search_redirects(t_ast *ast, t_pipex *pipex, t_env *env)
{
	if (ast->right)
	{
		if (ast->right->base->cmd_op == e_here_doc && ast->right->right->base
			->file_name)
			handle_heredocs(ast, pipex, env);
		if (check_redirect_type(ast))
			search_redirects(ast->right, pipex, env);
		if (ast->base->cmd_op == e_redirect_input
			&& ast->right->base->file_name)
			redirect_input_file(ast, pipex, env);
		if ((ast->base->cmd_op == e_redirect_output || ast->base->cmd_op
				== e_redirect_output_write_mod) && ast->right->base->file_name)
			redirect_output_file(ast, pipex, env);
	}
}

void	handle_heredocs(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int		heredoc_fd;
	char	*line;

	heredoc_fd = open("/tmp/heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (heredoc_fd == -1)
		error_management(e_file_name, cmd, pipex, NULL);
	while (true)
	{
		signal(SIGINT, &heredoc_sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		line = readline("heredoc> ");
		if (line == NULL)
		{
			close(heredoc_fd);
			ft_exit(NULL, cmd, env, pipex);
		}
		if (ft_strcmp(line, cmd->right->right->base->file_name) == 0)
		{
			free(line);
			break ;
		}
		heredoc_loop_cleanup(heredoc_fd, line);
	}
	heredoc_end(heredoc_fd, cmd, pipex);
}
