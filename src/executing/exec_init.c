/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:03:46 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/20 17:26:42 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pipex_init(t_ast *cmd, t_pipex *pipex, t_env *env)
{
	pipex->pipe_i = 0;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->ast_origin = cmd;
	if (env->nb_commands > 1)
		if (pipe(pipex->pipe_fd[0]) == -1 || pipe(pipex->pipe_fd[1]) == -1)
			error_management(e_pipe_failure, cmd, pipex, env);
	return (0);
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

char	*ft_getpath(char *cmd, t_env *env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*temp_path;

	i = -1;
	if (ft_strchr(cmd, '/') != NULL)
		return (ft_strdup(cmd));
	exec = find_env_var("PATH", env->envv);
	allpath = ft_split(exec, ':');
	free(exec);
	while (allpath[++i])
	{
		temp_path = ft_strjoin(allpath[i], "/", 0);
		exec = ft_strjoin(temp_path, ft_strdup(cmd), 2);
		if (access(exec, F_OK | X_OK) == 0 && check_dir(exec))
		{
			ft_free_double_array(allpath);
			return (exec);
		}
		free(exec);
	}
	ft_free_double_array(allpath);
	return (ft_strdup(cmd));
}

int	check_redirect_type(t_ast *ast)
{
	return (ast->right->base->cmd_op == e_redirect_input || ast->right->base
		->cmd_op == e_redirect_output || ast->right->base
		->cmd_op == e_redirect_output_write_mod);
}

void	heredoc_sigint_handler(int signal)
{
	if (signal == SIGINT)
		close(STDIN_FILENO);
}
