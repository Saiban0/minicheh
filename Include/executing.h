/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executing.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:44:47 by bchedru           #+#    #+#             */
/*   Updated: 2024/09/04 15:34:12 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTING_H
# define EXECUTING_H

typedef struct s_pipex
{
	int		pipe_fd[2];
	int		temp_fd;
	pid_t	pid;
	int		last_pid;
}				t_pipex;

void	exec_switch(t_ast *cmd, char **envp);
void	exec_extern(t_ast *cmd, char **envp);
void	exec_child(t_ast *cmd, char **envp);
void	exec_pipe_cmd(t_ast *cmd, char **envp, int curr_cmd, t_pipex *pipex);
int		open_file(char *file, int in_or_out, t_ast *cmd);
int		check_dir(char *cmd);
char	*ft_getpath(char *cmd);
void	ft_pipex_init(t_pipex *pipex);
void	create_pipe_fork(t_pipex *pipex, int i, t_ast *cmd);

#endif