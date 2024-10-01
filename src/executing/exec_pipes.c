/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:07:12 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/01 17:32:16 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_handle_pipe(t_ast *cmd, t_pipex *pipex, char **envp)
{
	if (cmd->right)
		exec_handle_pipe(cmd->right, pipex, envp);
	if (cmd->left)
		exec_handle_pipe(cmd->left, pipex, envp);
	if (!cmd->base->is_op)
	{
		pipex->pipe_i++;
		cmd->base->path = ft_getpath(cmd->base->cmd[0]);
		child_execution((*cmd->t_env)->nb_commands - pipex->pipe_i,
			cmd, pipex, envp);
	}
}

void	child_execution(int curr_cmd, t_ast *cmd, t_pipex *pipex, char **envp)
{
	if (curr_cmd == (*cmd->t_env)->nb_commands - 1)
	{
		create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			last_exec(curr_cmd, cmd, pipex, envp);
	}
	else if (curr_cmd == 0)
	{
		create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			first_exec(curr_cmd, cmd, pipex, envp);
	}
	else
	{
		create_fork(pipex, cmd);
		if (cmd->base->pid == 0)
			middle_exec(curr_cmd, cmd, pipex, envp);
	}
}

void	last_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, char **envp)
{
	int	fd;

	fd = get_fd(pipex->out_file, 1, cmd, pipex);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	close_pipes(cmd, pipex);
	if (cmd->base->path != NULL)
	{
		if (!cmd->base->builtins)
			execve(cmd->base->path, cmd->base->cmd, envp);
		// else
			// exec_builtins()
	}
	error_management(e_command_not_found, cmd, pipex);
}

void	middle_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, char **envp)
{
	dup2(pipex->pipe_fd[curr_cmd - 1][0], STDIN_FILENO);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	close_pipes(cmd, pipex);
	if (cmd->base->path != NULL)
	{
		if (!cmd->base->builtins)
			execve(cmd->base->path, cmd->base->cmd, envp);
		// else
			// exec_builtins()
	}
	error_management(e_command_not_found, cmd, pipex);
}

void	first_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, char **envp)
{
	int	fd;

	fd = get_fd(pipex->in_file, 0, cmd, pipex);
	dup2(fd, STDIN_FILENO);
	close(fd);
	dup2(pipex->pipe_fd[curr_cmd][1], STDOUT_FILENO);
	close_pipes(cmd, pipex);
	if (cmd->base->path != NULL)
	{
		if (!cmd->base->builtins)
			execve(cmd->base->path, cmd->base->cmd, envp);
		// else
			// exec_builtins()
	}
	error_management(e_command_not_found, cmd, pipex);
}
