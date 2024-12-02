/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/12/02 17:11:49 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_code;

void	without_op(char *line, t_ast	**ast)
{
	char	*temp;

	temp = rem_wspace(line);
	(*ast)->base->cmd = ft_split_arg(temp);
	(*ast)->base->quote_tab = result_quote_tab(temp);
	(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
	(*ast)->base->builtins = (*ast)->base->cmd_op >= e_echo;
	free(temp);
}
/*                                          */
int	count_tab_size(char *command)
{
	int		i;
	int		res;
	bool	env_var;
	char	*temp;

	i = -1;
	res = 1;
	env_var = false;
	temp = rem_wspace(command);
	while (temp[++i])
	{
		if (temp[i] == '$' && temp[i + 1] != '(')
		{
			env_var = true;
			res++;
		}
		else if (is_whitespace(temp[i]) && env_var == true)
		{
			env_var = false;
			res++;
		}
	}
	free(temp);
	return (res);
}

bool	cut_var(char *command, int *tab_int, char **res, char **envv)
{
	char	*temp;

	if (command[tab_int[0]] == '$' && command[tab_int[0] + 1] != '(')
	{
		res[tab_int[1]] = ft_calloc(tab_int[0] + 2, sizeof(char));
		ft_strlcat(res[tab_int[1]++], command, tab_int[0] + 1);
		tab_int[2] = true;
		return (true);
	}
	else if (is_whitespace(command[tab_int[0]]) && tab_int[2] == true)
	{
		temp = ft_calloc(tab_int[0] + 1, sizeof(char));
		ft_strlcat(temp, command, tab_int[0] + 1);
		res[tab_int[1]++] = find_env_var(temp, envv);
		free(temp);
		tab_int[2] = false;
		return (true);
	}
	tab_int[0] += 1;
	return (false);
}
/*
 * tab_int[0] = i;
 * tab_int[1] = j;
 * tab_int[2] = env_var;
 */
char	**ft_split_env_arg(char *command, int res_size, char **envv)
{
	int		tab_int[3];
	char	**res;
	char	*temp;

	tab_int[0] = 0;
	tab_int[1] = 0;
	tab_int[2] = false;
	res = ft_calloc(res_size, sizeof(char *));
	while (command[tab_int[0]])
	{
		if (command[tab_int[0]] == '$' && command[tab_int[0] + 1] != '(')
		{
			res[tab_int[1]] = ft_calloc(tab_int[0] + 2, sizeof(char));
			ft_strlcat(res[tab_int[1]++], command, tab_int[0] + 1);
			tab_int[2] = true;
			command += tab_int[0];
			tab_int[0] = 0;
		}
		else if (is_whitespace(command[tab_int[0]]) && tab_int[2] == true)
		{
			temp = ft_calloc(tab_int[0] + 2, sizeof(char));
			ft_strlcat(temp, command, tab_int[0] + 1);
			res[tab_int[1]++] = find_env_var(temp, envv);
			free(temp);
			tab_int[2] = false;
			command += tab_int[0];
			tab_int[0] = 0;
		}
		tab_int[0]++;
	}
	if (command[0] == '$')
		res[tab_int[1]++] = find_env_var(command, envv);
	else
	{
		res[tab_int[1]] = ft_calloc(tab_int[0] + 1, sizeof(char));
		ft_strlcat(res[tab_int[1]++], command, tab_int[0] + 1);
	}
	res[tab_int[1]] = NULL;
	return (res);
}

static int	join_size(char **array)
{
	int	i;
	int	j;
	int res;

	i = -1;
	res = 0;
	while (array[++i])
	{
		j = -1;
		while (array[i][++j])
			res++;
	}
	return (res + 1);
}

char	*ft_join_env_arg(char **array)
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = 0;
	j = 0;
	k = 0;
	res = malloc(join_size(array) * sizeof(char));
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			res[k] = array[i][j];
			j++;
			k++;
		}
		free(array[i]);
		i++;
	}
	free(array);
	res[k] = '\0';
	return (res);
}
/*                                          */

void	env_var_handler(t_ast **ast, t_env **env_start, int i)
{
	char	**d_array_temp;
	char	*temp;

	temp = rem_wspace((*ast)->base->cmd[i]);
	d_array_temp = ft_split_env_arg(temp,
			count_tab_size((*ast)->base->cmd[i]) + 1, (*env_start)->envv);
	free((*ast)->base->cmd[i]);
	free(temp);
	(*ast)->base->cmd[i] = ft_join_env_arg(d_array_temp);
}

void	env_var_test(t_ast **ast, t_env **env_start)
{
	int		i;
	
	i = -1;
	(void)env_start;
	while ((*ast)->base->cmd[++i])
		if ((*ast)->base->quote_tab[i] != '\'')
			env_var_handler(ast, env_start, i);
	free((*ast)->base->quote_tab);
	// if ((*ast)->base->cmd[i][0] == '$' && (*ast)->base->cmd[i][1] == '?')
	// {
	// 	free((*ast)->base->cmd[i]);
	// 	(*ast)->base->cmd[i] = ft_itoa(g_exit_code);
	// }
	// else if ((*ast)->base->cmd[i][0] == '$' && (*ast)->base->cmd[i][1] != '(')
	// {
	// 	temp = find_env_var((*ast)->base->cmd[i], (*env_start)->envv);
	// 	free((*ast)->base->cmd[i]);
	// 	(*ast)->base->cmd[i] = ft_strdup(temp);
	// 	free(temp);
	// }
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

void	end_of_parse(char *line, t_ast	**ast)
{
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
	end_of_parse(line, ast);
	env->nb_commands = 0;
	add_env(&env, ast);
}
