/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:09:02 by tom               #+#    #+#             */
/*   Updated: 2024/10/10 18:27:04 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	i = double_array_size(envp);
	env = ft_calloc(1, sizeof(t_env));
	env->pwd = ft_strdup(getenv("PWD"));
	env->envv = ft_calloc(i + 1, sizeof(char*));
	i = -1;
	while (envp[++i])
	{
		env->envv[i] = ft_strdup(envp[i]);
		if (errno == ENOMEM)
		{
			ft_free_double_array(env->envv);
			return (NULL);
		}
	}
	return (env);
}

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		write(STDERR_FILENO, "\n", 1);
		exit(0);
	}
}

bool	loop(t_env	*env)
{
	char	*line;
	t_ast	*ast;

	write(1, "minicheh -> ", 13);
	line = get_next_line(0);
	if (line[0] == '\n')
		return (false);
	ast = ft_calloc(1, sizeof(t_ast) + 1);
	ast->base = ft_calloc(1, sizeof(t_ast_content) + 1);
	env->nb_commands = 0;
	parse(line, &ast, env);
	free(line);
	exec_switch(ast, env);
	// free_ast(ast);
	return (true);
}

int main(int ac, char **av, char **envp)
{

	t_env	*env;

	(void)av;
	if (ac > 1)
	{
		write(STDERR_FILENO, "Usage : ./minishell\n", 21);
		return (EXIT_FAILURE);
	}
	env = init_env(envp);
	if (!env)
		return (EXIT_FAILURE);
	while (true)
	{
		errno = 0;
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &sigint_handler);
		if (!loop(env))
			continue;
	}
	free(env->envv);
	free(env->pwd);
	free(env);
}

