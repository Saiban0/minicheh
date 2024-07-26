/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/07/26 14:07:42 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_and_op	is_builtins(char *command)
{
	command = rem_wspace(command);
	if (ft_strncmp(command,"echo", 4) == 0)
			return (e_echo);
	if (ft_strncmp(command,"cd", 2) == 0)
		return (e_cd);
	if (ft_strncmp(command,"pwd", 3) == 0)
			return (e_pwd);
	if (ft_strncmp(command,"export", 6) == 0)
			return (e_export);
	if (ft_strncmp(command,"unset", 5) == 0)
			return (e_unset);
	if (ft_strncmp(command,"exit", 4) == 0)
			return (e_exit);
	if (ft_strncmp(command,"env", 3) == 0)
			return (e_env);
	return (e_external_control);
}

void	last_command(char *line, t_ast	**ast)
{
	(*ast)->base->cmd = ft_split(line, ' ');
	(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
}

void	select_operator(char	*line, int	i, t_ast	**ast)
{
	if (line[i] == '|')
		ast_pipe(line, i, ast);
	else if (line[i] == '<' && line[i + 1] == '<')
		ast_else(line, i + 1, ast, e_here_doc);
	else if (line[i] == '>' && line[i + 1] == '>')
		ast_else(line, i + 1, ast, e_redirect_output_write_mod);
	else if (line[i] == '>')
		ast_else(line, i, ast, e_redirect_output);
	else if (line[i] == '<')
		ast_else(line, i, ast, e_redirect_input);
}

int		add_env(t_env	**env_start, t_ast	**ast)
{
	int	res ;

	res = 0;
	res += ((*ast)->base->cmd_op != e_empty);
	(*ast)->t_env = env_start;
	if ((*ast)->left)
		res = (add_env(env_start, &(*ast)->left));
	if ((*ast)->right)
		res = (add_env(env_start, &(*ast)->right));
	return (res);
}

void	parse(char *line, t_ast	**ast, t_env	*env_start)
{
	int		i;

	i = -1;
	(void)env_start;
	(*ast)->base->cmd_op = e_empty;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	(*ast)->t_env = NULL;
	while (line[++i])
	{
		if (is_op(line[i]))
		{
			select_operator(line, i, ast);
			line += i;
			i = 0;
		}
	}
	if ((*ast)->base->cmd_op == e_empty)
		last_command(line, ast);
	// env_start->ast_size = add_env(&env_start, ast);
	// ft_printf("%d", (*(*ast)->t_env)->ast_size);
}
