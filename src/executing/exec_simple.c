/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_simple.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:16:54 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/04 15:34:09 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_switch(t_ast *cmd, char **envp)
{
	t_pipex	*pipex;

	ft_pipex_init(pipex);
	if (cmd->base->cmd[0][0] == '\0')
		error_management(e_empty_command, cmd);
	if (cmd->base->is_op)
	{
		if (cmd->base->cmd_op == e_pipe)
			exec_handle_pipe(cmd, envp);
		// if (cmd->base->cmd_op == e_redirect_input)
		// 	handle_redirect_input(cmd, envp);
		// if (cmd->base->cmd_op == e_redirect_output)
		// 	handle_redirect_output(cmd, envp);
	}
	else if (cmd->base->cmd_op == e_external_control)
		exec_extern(cmd, envp);
}

void	exec_extern(t_ast *cmd, char **envp)
{
	pid_t	new_pid;
	int		status;

	new_pid = fork();
	if (new_pid == -1)
		error_management(e_fork_failure, cmd);
	if (new_pid == 0)
		exec_child(cmd, envp);
	waitpid(new_pid, &status, 0);
}

void	exec_child(t_ast *cmd, char **envp)
{
	char	*cmd_path;

	cmd_path = "";
	// if (cmd->base->builtins)
		// handle_builtins(cmd, envp);
	cmd_path = ft_getpath(cmd->base->cmd[0]);
	if (execve(cmd_path, cmd->base->cmd, envp) == -1)
	{
		free(cmd_path);
		error_management(e_command_not_found, cmd);
	}
}


void	exec_pipe_cmd(t_ast *cmd, char **envp, int curr_cmd, t_pipex *pipex)
{
	if (curr_cmd < (cmd->nb_commands - 1) && (pipe(pipex->pipe_fd) == -1))
		error_management(e_pipe_failure, cmd);
	create_pipe_fork(pipex, curr_cmd, cmd);
	if (curr_cmd == 0)
		pipex->last_pid = pipex->pid;
	if (curr_cmd < (cmd->nb_commands - 1) && pipex->pipe_fd[0] != -1)
		close(pipex->pipe_fd[0]);
	if (pipex->pid != 0)
		waitpid(pipex->last_pid, 0, 0);
}

void	create_pipe_fork(t_pipex *pipex, int i, t_ast *cmd)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
		error_management(e_pipe_failure, cmd);
		cmd_switch(pipex, cmd, i);
	
}

void	cmd_switch()

void	ft_output(t_pipex *pipex, t_ast *arg, int fd_status)
{
	int	out_fd;

	out_fd = -1;
	if (!arg->output && fd_status == 0)
		return ;
	if (arg->output)
	{
		if (arg->output_type == 1)
			out_fd = open(arg->output, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else if (arg->output_type == 0)
			out_fd = open(arg->output, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (pipex->temp_fd_out != -1)
			close (pipex->temp_fd_out);
	}
	else
		out_fd = pipex->temp_fd_out;
	if (out_fd == -1)
		_open_fail(pipex, main);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		ft_write_join(SHIT, " dup2 failed:", "", " output");
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		ft_pipex_error(pipex, main, EXIT_FAILURE);
	if (out_fd != -1)
		close(out_fd);
}