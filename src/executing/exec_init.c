/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 12:03:46 by bchedru           #+#    #+#             */
/*   Updated: 2024/10/01 12:05:50 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**extract_paths(char **envp)
{
	int		i;
	char	*tmp;
	char	**list;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	list = ft_split(envp[i], ':');
	if (!list)
		return (NULL);
	tmp = ft_strtrim(envp[i], "PATH=");
	if (!tmp)
		return (NULL);
	free(list[0]);
	list[0] = tmp;
	return (list);
}

void	ft_pipex_init(t_ast *cmd, t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	pipex->path_list = extract_paths(envp);
	if (!pipex->path_list)
		error_management(e_env_error, cmd, pipex);
	pipex->pipe_i = 0;
	pipex->in_file = "/dev/stdin";
	pipex->out_file = "/dev/stdout";
	pipex->pipe_fd = malloc((cmd->nb_commands - 1) * sizeof(int [2]));
	if (!pipex->pipe_fd)
		error_management(e_malloc_failure, cmd, pipex);
	while (i < cmd->nb_commands - 1)
	{
		if (pipe(pipex->pipe_fd[i]) == -1)
			error_management(e_pipe_failure, cmd, pipex);
		i++;
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
	char	**curr_cmd;

	i = -1;
	allpath = ft_split(getenv("PATH"), ':');
	curr_cmd = ft_split(cmd, ' ');
	while (allpath[++i])
	{
		temp_path = ft_strjoin(allpath[i], "/", 0);
		exec = ft_strjoin(temp_path, curr_cmd[0], 1);
		if (access(exec, F_OK | X_OK) == 0 && check_dir(exec))
		{
			ft_free_double_array(curr_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_double_array(allpath);
	ft_free_double_array(curr_cmd);
	return (cmd);
}
