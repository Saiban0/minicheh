/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/06/26 05:11:29 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	safe_exit(t_ast	**ast, char *line)
{
	if (ast)
	{
		// Faire une fonction qui free l'ast complet pas dure mais long et prise
		// de tete.
		// Plus simple apres a voir une bonne connaissance des metode de
		// deplacement dans un arbre.
		free(ast);
	}
	if (line)
		free(line);
	exit(0);
}

bool	is_op(char	line)
{
	if (line == '|')
		return (1);
	else if (line == '<')
		return (1);
	else if (line == '>')
		return (1);
	return (0);
}

bool	is_whitespace(char	c)
{
	return (c == ' ' || c == '\t' || c == '\v' || c == '\n');
}

char	*rem_wspace(char *commande)
{
	int	i;

	i = 0;
	while(is_whitespace(commande[i]))
		commande++;
	i = ft_strlen(commande);
	if (is_whitespace(commande[i]))
	{
		while(is_whitespace(commande[--i]))
			continue;
		commande[i] = '\0';
	}
	return (commande);
}

bool	is_builtins(char *commande)
{
	commande = rem_wspace(commande);
	if (ft_strncmp(commande,"echo", 4) == 0)
		if (is_whitespace(commande[4]) || is_op(commande[4]))
			return (true);
	if (ft_strncmp(commande,"cd", 2) == 0)
		if (is_whitespace(commande[2]) || is_op(commande[2]))
		return (true);
	if (ft_strncmp(commande,"pwd", 3) == 0)
		if (is_whitespace(commande[3]) || is_op(commande[3]))
			return (true);
	if (ft_strncmp(commande,"export", 6) == 0)
		if (is_whitespace(commande[6]) || is_op(commande[6]))
			return (true);
	if (ft_strncmp(commande,"unset", 5) == 0)
		if (is_whitespace(commande[5]) || is_op(commande[5]))
			return (true);
	if (ft_strncmp(commande,"exit", 4) == 0)
		if (is_whitespace(commande[4]) || is_op(commande[4]))
			return (true);
	if (ft_strncmp(commande,"env", 3) == 0)
		if (is_whitespace(commande[3]) || is_op(commande[3]))
			return (true);
	return (false);
}

void	fill_ast(char	*line, int	i, t_ast	**ast)
{
	char	*tmp;

	tmp = malloc (sizeof(char) * i + 1);
	if (!tmp)
		safe_exit(ast, line);
	if (line[i] == '|')
	{
		(*ast)->base->cmd_op = e_pipe;
		while(i--)
			tmp[i] = line[i];
		if (is_builtins(tmp))
			exit(0);
	}
}

t_ast	*parse(char *line)
{
	t_ast	*ast;
	int		i;

	i = -1;
	while (line[++i])
	{
		if (is_op(line[i]))
		{
			fill_ast(line, i, &ast);
			line += i;
			i = 0;
		}
	}
	return (ast);
}
