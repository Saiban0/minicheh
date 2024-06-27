/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:25:44 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/27 13:55:07 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(char *file, int in_or_out, t_ast *cmd)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (ret == -1)
		error_management(e_file_not_found, cmd);
	return (ret);
}

int	check_dir(char *cmd)
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
		exec = ft_strjoin(temp_path, curr_cmd[0], 0);
		free(temp_path);
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
