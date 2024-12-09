/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/12/09 14:18:44 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	without_op(char *line, t_ast	**ast)
{
	char	*temp;

	temp = rem_wspace(line);
	(*ast)->base->cmd = ft_split_arg(temp);
	(*ast)->base->quote_tab = result_quote_tab(temp, NULL);
	(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
	(*ast)->base->builtins = (*ast)->base->cmd_op >= e_echo;
	free(temp);
}

void	env_var_test(t_ast **ast, t_env **env_start)
{
	int		i;

	i = -1;
	while ((*ast)->base->cmd[++i])
		if ((*ast)->base->quote_tab[i] != '\''
			&& ft_strchr((*ast)->base->cmd[i], '$') != NULL)
			env_var_handler(ast, env_start, i);
	free((*ast)->base->quote_tab);
}

void	add_env(t_env	**env_start, t_ast	**ast)
{
	(*ast)->t_env = env_start;
	(*ast)->base->path = NULL;
	(*env_start)->nb_commands += ((*ast)->base->cmd_op == e_external_control)
		|| ((*ast)->base->cmd_op >= e_echo);
	if ((*ast)->base->cmd_op != e_file_name)
		(*ast)->base->file_name = NULL;
	if (!(((*ast)->base->cmd_op == e_external_control)
			|| ((*ast)->base->cmd_op >= e_echo)))
		(*ast)->base->cmd = NULL;
	else
		env_var_test(ast, env_start);
	if ((*ast)->left)
		add_env(env_start, &(*ast)->left);
	if ((*ast)->right)
		add_env(env_start, &(*ast)->right);
}

void	parse(char *line, t_ast	**ast, t_env *env, int quote)
{
	int		i;

	i = -1;
	(*ast)->base->cmd_op = e_empty;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	(*ast)->t_env = &env;
	if (!open_quote_pipe_test(line, ast, env))
		return ;
	while (line[++i])
	{
		if (line[i] == '"' || line[i] == '\'')
			quote = quote_test(line[i], quote);
		if (is_op(line[i]) && quote == 0)
		{
			if (select_operator(line, i, ast) == false)
				return (parse_error_handler(e_unexpected_newline, ast));
			line += i + (line[i] == line[i + 1]);
			i = 0;
		}
	}
	if ((*ast)->base->cmd_op == e_empty)
		without_op(line, ast);
	env->nb_commands = 0;
	add_env(&env, ast);
}
