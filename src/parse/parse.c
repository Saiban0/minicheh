/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/10/11 11:44:35 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	without_op(char *line, t_ast	**ast)
{
	(*ast)->base->cmd = ft_split(line, ' ');
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
	return (true);
}

void	add_env(t_env	**env_start, t_ast	**ast)
{
	(*env_start)->nb_commands += ((*ast)->base->cmd_op == e_external_control)
		|| ((*ast)->base->cmd_op >= e_echo);
	(*ast)->t_env = env_start;
	(*ast)->base->path = NULL;
	if (!(*ast)->base->file_name)
		(*ast)->base->file_name = NULL;
	if ((*ast)->left)
		add_env(env_start, &(*ast)->left);
	if ((*ast)->right)
		add_env(env_start, &(*ast)->right);
}

void	parse(char *line, t_ast	**ast, t_env	*env_start)
{
	int		i;

	i = -1;
	(*ast)->base->cmd_op = e_empty;
	(*ast)->left = NULL;
	(*ast)->right = NULL;
	(*ast)->t_env = &env_start;
	line[ft_strlen(line) - 1] = '\0';
	while (line[++i])
	{
		if (is_op(line[i]))
		{
			if (select_operator(line, i, ast) == false)
			{
				write(1, "minishell: ", 12);
				write(1, "syntax error near unexpected token `newline'\n", 46);
				return ;
			}
			line += i + (line[i] == line[i + 1]);
			i = 0;
		}
	}
	if ((*ast)->base->cmd_op == e_empty)
		without_op(line, ast);
	env_start->nb_commands = 0;
	add_env(&env_start, ast);
	// Problème de size avec '<<' et '>>'
	// rajoute 2 à la taille total (problème qui viens de la création de l'ast)
}