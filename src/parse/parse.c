/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 19:12:58 by tom               #+#    #+#             */
/*   Updated: 2024/06/28 02:53:07 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_cmd_and_op	is_builtins(char *commande)
{
	commande = rem_wspace(commande);
	if (ft_strncmp(commande,"echo", 4) == 0)
			return (e_echo);
	if (ft_strncmp(commande,"cd", 2) == 0)
		return (e_cd);
	if (ft_strncmp(commande,"pwd", 3) == 0)
			return (e_pwd);
	if (ft_strncmp(commande,"export", 6) == 0)
			return (e_export);
	if (ft_strncmp(commande,"unset", 5) == 0)
			return (e_unset);
	if (ft_strncmp(commande,"exit", 4) == 0)
			return (e_exit);
	if (ft_strncmp(commande,"env", 3) == 0)
			return (e_env);
	return (e_external_control);
}

void	first_base(char	*commande, char	*line, t_ast	**ast, int	*operator)
{
	char	*tmp;
	
	tmp = ft_calloc(operator[0] + 2, sizeof(char));
	ft_strlcat(commande, line, operator[1]);
	ft_strlcat(tmp, line, operator[0] + 1);
	tmp = rem_wspace(tmp);
	(*ast)->base->cmd_op = e_pipe;
	(*ast)->base->is_op = true;
	(*ast)->left = malloc(sizeof(t_ast *));
	(*ast)->left->base = malloc(sizeof(t_ast_content *));
	(*ast)->left->base->cmd = ft_split(tmp, ' ');
	(*ast)->left->base->cmd_op = is_builtins((*ast)->left->base->cmd[0]);
	free(tmp);
}

void	ast_pipe(char	*line, int	i, t_ast	**ast)
{
	char	*commande;
	int		operator[2];
	char	*tmp;

	operator[0] = i;
	operator[1] = i + 1;
	while (line[operator[1]] && !is_op(line[operator[1]]))
		operator[1]++;
	commande = ft_calloc(operator[1] + 1, sizeof(char));
	if ((*ast)->base->cmd_op == e_empty)
		first_base(commande, line, ast, operator);
	else
	{
		ft_printf("a faire");
		exit(0);
	}
	line += i + 1;
	tmp = ft_calloc(operator[1] - i + 1, sizeof(char));
	ft_strlcat(tmp, line, operator[1] - i);
	(*ast)->right = malloc(sizeof(t_ast *));
	(*ast)->right->base = malloc(sizeof(t_ast_content *));
	(*ast)->right->base->cmd = ft_split(tmp, ' ');
	(*ast)->right->base->cmd_op = is_builtins((*ast)->right->base->cmd[0]);
	free(commande);
	free(tmp);
}

t_ast	*parse(char *line)
{
	t_ast	*ast;
	int		i;

	i = -1;
	ast = malloc(sizeof(t_ast *));
	ast->base = malloc(sizeof(t_ast_content *));
	ast->base->cmd_op = e_empty;
	while (line[++i])
	{
		if (line[i] == '|')
		{
			ast_pipe(line, i, &ast);
			line += i;
			i = 0;
			return (NULL);
		}
	}
	return (NULL);
}
