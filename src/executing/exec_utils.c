/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:25:44 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/16 19:21:01 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_builtins(t_ast *cmd, t_env *env)
{
	(void)env;
	if (cmd->base->cmd_op >= e_echo)
	{
		if (cmd->base->cmd_op == e_echo)
			ft_echo(cmd->base->cmd);
		if (cmd->base->cmd_op == e_cd)
			ft_cd(cmd->base->cmd, &env);
		if (cmd->base->cmd_op == e_pwd)
			ft_pwd(cmd->base->cmd, env);
		// if (cmd->base->cmd_op == e_export)
		// 	ft_export(cmd->base->cmd);
		// if (cmd->base->cmd_op == e_unset)
		// 	ft_unset(cmd->base->cmd);
		// if (cmd->base->cmd_op == e_exit)
		// 	ft_exit(cmd->base->cmd);
		if (cmd->base->cmd_op == e_env)
			ft_env(cmd->base->cmd, env);
	}
}

void	close_pipes(t_pipex *pipex, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->nb_commands - 1)
	{
		close(pipex->pipe_fd[i][0]);
		close(pipex->pipe_fd[i][1]);
		i++;
	}
}

void	wait_execution(t_ast *cmd, int *status)
{
	if (cmd->right)
		wait_execution(cmd->right, status);
	if (cmd->left)
		wait_execution(cmd->left, status);
	if (!cmd->base->is_op)
		waitpid(cmd->base->pid, status, 0);
}

void	create_fork(t_pipex *pipex, t_ast *cmd)
{
	cmd->base->pid = fork();
	if (cmd->base->pid == -1)
		error_management(e_fork_failure, cmd, pipex);
}

int	get_fd(char *file_name, bool read_or_write, t_ast *cmd, t_pipex *pipex)
{
	int	fd;

	fd = -1;
	if (ft_strcmp(file_name, "/dev/stdin") == 0)
		return (STDIN_FILENO);
	if (ft_strcmp(file_name, "/dev/stdout") == 0)
		return (STDOUT_FILENO);
	if (!read_or_write)
		fd = open(file_name, O_RDONLY);
	else
	{
		if (pipex->append)
			fd = open(file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (fd == -1)
		error_management(e_file, cmd, pipex);
	return (fd);
}
