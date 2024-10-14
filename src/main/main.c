/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:09:02 by tom               #+#    #+#             */
/*   Updated: 2024/10/14 22:04:40 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*init_env(char **envp)
{
	t_env	*env;
	int		i;

	i = -1;
	env = ft_calloc(1, sizeof(t_env));
	env->envv = ft_calloc(double_array_size(envp) + 1, sizeof(char*));
	while (envp[++i])
	{
		env->envv[i] = ft_strdup(envp[i]);
		if (errno == ENOMEM)
		{
			ft_free_double_array(env->envv);
			return (NULL);
		}
	}
	i = -1;
	while (env->envv[++i])
	{
		if (ft_strncmp(env->envv[i], "PWD", 3) == 0)
			env->pwd_position = i;
		if (ft_strncmp(env->envv[i], "OLDPWD", 6) == 0)
			env->oldpwd_position = i;
		if (ft_strncmp(env->envv[i], "HOME", 4) == 0)
			env->home_position = i;
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
	line = NULL;
	// exec_switch(ast, env);
	free_ast(ast);
	ast = NULL;
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
	ft_free_double_array(env->envv);
	free(env);
}

