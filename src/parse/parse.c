/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/11/15 18:45:40 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	without_op(char *line, t_ast	**ast)
{
	char	*temp;

	temp = rem_wspace(line);
	(*ast)->base->cmd = ft_split_arg(temp, ' ');
	(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
	(*ast)->base->builtins = (*ast)->base->cmd_op >= e_echo;
	free(temp);
}

void	env_var_handle(t_ast **ast, t_env **env_start, char *temp, int i)
{
	if ((*ast)->base->cmd[i][0] == '$' && (*ast)->base->cmd[i][1] == '?')
	{
		free((*ast)->base->cmd[i]);
		(*ast)->base->cmd[i] = ft_itoa(g_exit_code);
	}
	else if ((*ast)->base->cmd[i][0] == '$' && (*ast)->base->cmd[i][1] != '(')
	{
		temp = find_env_var((*ast)->base->cmd[i], (*env_start)->envv);
		free((*ast)->base->cmd[i]);
		(*ast)->base->cmd[i] = ft_strdup(temp);
		free(temp);
	}
}

void	add_env(t_env	**env_start, t_ast	**ast)
{
	int		i;
	char	*temp;

	i = -1;
	temp = NULL;
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
		while ((*ast)->base->cmd[++i])
			env_var_handle(ast, env_start, temp, i);
	if ((*ast)->left)
		add_env(env_start, &(*ast)->left);
	if ((*ast)->right)
		add_env(env_start, &(*ast)->right);
}

void	end_of_parse(int quote, char *line, t_ast	**ast, t_env *env)
{
	if (quote == '"')
		open_quote("dquote> ", ast, env, line);
	if (quote == '\'')
		open_quote("quote> ", ast, env, line);
	if ((*ast)->base->cmd_op == e_empty)
		without_op(line, ast);
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
	end_of_parse(quote, line, ast, env);
	env->nb_commands = 0;
	add_env(&env, ast);
}
