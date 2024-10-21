/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:03:46 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/21 16:09:11 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipex_init(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	int	i;

	i = 0;
	pipex->pipe_i = 0;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->nb_commands = env->nb_commands;
	pipex->pipe_fd = malloc((env->nb_commands - 1) * sizeof(int [2]));
	if (!pipex->pipe_fd)
		error_management(e_malloc_failure, cmd, pipex);
	while (i < env->nb_commands - 1 && cmd->base->cmd_op == e_pipe)
	{
		if (pipe(pipex->pipe_fd[i]) == -1)
			error_management(e_pipe_failure, cmd, pipex);
		i++;
	}
}

static int	check_redirect_type(t_ast *ast)
{
	return (ast->right->base->cmd_op == e_redirect_input || ast->right->base
		->cmd_op == e_redirect_output || ast->right->base
		->cmd_op == e_redirect_output_write_mod);
}

void	redirect_input_file(t_ast *ast, t_pipex *pipex)
{
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	pipex->in_fd = get_fd(ast->right->base->file_name, 0, ast, pipex);
	if (ast->right->right)
		search_redirects(ast->right->right, pipex);
}

void	redirect_output_file(t_ast *ast, t_pipex *pipex)
{
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	if (ast->base->cmd_op == e_redirect_output)
		pipex->out_fd = get_fd(ast->right->base->file_name, 1, ast, pipex);
	if (ast->base->cmd_op == e_redirect_output_write_mod)
		pipex->out_fd = get_fd(ast->right->base->file_name, 2, ast, pipex);
	if (ast->right->right)
		search_redirects(ast->right->right, pipex);
}

void	search_redirects(t_ast *ast, t_pipex *pipex)
{
	if (ast->right)
	{
		if (ast->right->base->cmd_op == e_here_doc && ast->right->right->base
			->file_name)
			handle_heredocs(ast, pipex);
		if (check_redirect_type(ast))
			search_redirects(ast->right, pipex);
		if (ast->base->cmd_op == e_redirect_input
			&& ast->right->base->file_name)
			redirect_input_file(ast, pipex);
		if ((ast->base->cmd_op == e_redirect_output || ast->base->cmd_op
				== e_redirect_output_write_mod) && ast->right->base->file_name)
			redirect_output_file(ast, pipex);
	}
}

static int	check_dir(char *cmd)
{
	int	fd;

	fd = open(cmd, __O_DIRECTORY);
	if (fd != -1)
	{
		close(fd);
		return (-1);
	}
	if (errno == ENOTDIR)
		return (1);
	return (0);
}

char	*ft_getpath(char *cmd)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*temp_path;

	i = -1;
	allpath = ft_split(getenv("PATH"), ':');
	while (allpath[++i])
	{
		temp_path = ft_strjoin(allpath[i], "/", 0);
		exec = ft_strjoin(temp_path, cmd, 1);
		if (access(exec, F_OK | X_OK) == 0 && check_dir(exec))
		{
			ft_free_double_array(allpath);
			return (exec);
		}
		free(exec);
	}
	ft_free_double_array(allpath);
	return (cmd);
}
