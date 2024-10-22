/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/10/22 20:26:45 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	without_op(char *line, t_ast	**ast)
{
	(*ast)->base->cmd = ft_split_arg(line, ' ');
	(*ast)->base->cmd_op = is_builtins((*ast)->base->cmd[0]);
	(*ast)->base->builtins = (*ast)->base->cmd_op >= e_echo;

}

bool	select_operator(char	*line, int	i, t_ast	**ast)
{
	int	j;

	j = i + 1;
	while (line[j] && is_whitespace(line[j]) == true)
		j++;
	if (!line[j])
		return (false);
	// A gérer le cas ou c'est un pipe en fin de ligne
	// Même fonctionnement que avec un " en fin de ligne
	// (Ouvrir les guillemets)
	if (line[i] == '|' && line[i + 1] == '|')
		ft_exit(line, *ast, *(*ast)->t_env);
	else if (line[i] == '|')
		ast_pipe(line, i, ast);
	else if (line[i] == '<' && line[i + 1] == '<')
		ast_else(line, i + 1, ast, e_here_doc);
	else if (line[i] == '>' && line[i + 1] == '>')
		ast_else(line, i + 1, ast, e_redirect_output_write_mod);
	else if (line[i] == '>')
		ast_else(line, i, ast, e_redirect_output);
	else if (line[i] == '<')
		ast_else(line, i, ast, e_redirect_input);
	return (true);
}

char	*find_env_var(char	*var, char	**envv)
{
	int	i;
	int	var_size;

	i = -1;
	var++;
	var_size = ft_strlen(var);
	while (envv[++i])
	{
		if (ft_strncmp(var, envv[i], var_size - 1) == 0)
			return (ft_strdup(envv[i] + var_size + 1));
	}
	return (ft_strdup(" "));
}

void	add_env(t_env	**env_start, t_ast	**ast)
{
	int		i;
	char	*temp;
	
	(*env_start)->nb_commands += ((*ast)->base->cmd_op == e_external_control)
		|| ((*ast)->base->cmd_op >= e_echo);
	(*ast)->t_env = env_start;
	(*ast)->base->path = NULL;
	if ((*ast)->base->cmd_op != e_file_name)
		(*ast)->base->file_name = NULL;
	if (!(((*ast)->base->cmd_op == e_external_control) || ((*ast)->base->cmd_op >= e_echo)))
		(*ast)->base->cmd = NULL;
	else
	{
		i = -1;
		while ((*ast)->base->cmd[++i])
		{
			if ((*ast)->base->cmd[i][0] == '$' && (*ast)->base->cmd[i][1] != '(')
			{
				temp = find_env_var((*ast)->base->cmd[i], (*env_start)->envv);
				free((*ast)->base->cmd[i]);
				(*ast)->base->cmd[i] = ft_strdup(temp);
				free(temp);
			}
		}
	}
	if ((*ast)->left)
		add_env(env_start, &(*ast)->left);
	if ((*ast)->right)
		add_env(env_start, &(*ast)->right);
}

// Remplacer les utilisations de ft_split par une fonction qui va gérer les quotes et les espace d'elle même.
// Nécessite des modifications dans le parse.

void	parse(char *line, t_ast	**ast, t_env	*env)
{
	int		i;

	i = -1;
	(*ast)->base->cmd_op = e_empty;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	(*ast)->t_env = &env;
	line[ft_strlen(line) - 1] = '\0';
	while (line[++i])
	{
		if (is_op(line[i]))
		{
			if (select_operator(line, i, ast) == false)
			{
				ft_putstr_fd("minishell: ", STDERR_FILENO);
				ft_putstr_fd("syntax error near unexpected token `newline'\n", STDERR_FILENO);
				return ;
			}
			line += i + (line[i] == line[i + 1]);
			i = 0;
		}
	}
	if ((*ast)->base->cmd_op == e_empty)
		without_op(line, ast);
	env->nb_commands = 0;
	add_env(&env, ast);
	free(line);
}
