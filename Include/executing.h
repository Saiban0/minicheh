/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:44:47 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/01 12:08:00 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

typedef struct s_pipex
{
	int		temp_fd;
	int		pipe_i;
	char	*in_file;
	char	*out_file;
	char	**path_list;
	int		(*pipe_fd)[2];
	int		status;
}				t_pipex;

void	exec_switch(t_ast *cmd, char **envp);
void	exec_simple(t_ast *cmd, char **envp, t_pipex *pipex);
void	exec_only_child(t_ast *cmd, t_pipex *pipex, char **envp);
void	exec_handle_pipe(t_ast *cmd, t_pipex *pipex, char **envp);
void	child_execution(int cur_cmd, t_ast *cmd, t_pipex *pipex, char **envp);
void	last_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, char **envp);
void	middle_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, char **envp);
void	first_exec(int curr_cmd, t_ast *cmd, t_pipex *pipex, char **envp);
char	*ft_getpath(char *cmd);
void	ft_pipex_init(t_ast *cmd, t_pipex *pipex, char **envp);
void	close_pipes(t_ast *cmd, t_pipex *pipex);
void	wait_execution(t_ast *cmd, int *status);
void	create_fork(t_pipex *pipex, t_ast *cmd);
int		get_fd(char *file_name, int read_or_write, t_ast *cmd, t_pipex *pipex);

#endif