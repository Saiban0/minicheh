/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:09:02 by tom               #+#    #+#             */
/*   Updated: 2024/11/04 15:57:47 by bchedru          ###   ########.fr       */
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
	env->quote = false;
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
		{
			env->pwd = ft_strdup(env->envv[i]);
			env->pwd_position = i;
		}
		if (ft_strncmp(env->envv[i], "OLDPWD", 6) == 0)
		{
			env->oldpwd = ft_strdup(env->envv[i]);
			env->oldpwd_position = i;
		}
		if (ft_strncmp(env->envv[i], "HOME", 4) == 0)
			env->home_position = i;
	}
	return (env);
}

volatile bool test_sig;

void	sigint_handler(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

bool	loop(t_env	*env)
{
	char	*line;
	t_ast	*ast;
	char	**temp;

	line = readline("$ ");
	if (!line)
		ft_exit(NULL, NULL, env, NULL);
	if (line[0] == '\0')
		return (false);
	add_history(line);
	ast = ft_calloc(1, sizeof(t_ast) + 1);
	ast->base = ft_calloc(1, sizeof(t_ast_content) + 1);
	env->nb_commands = 0;
	if (only_wspace(line))
	{
		free(line);
		free_ast(ast);
		return (false);
	}
	parse(line, &ast, env);
	free(line);
	line = NULL;
	exec_switch(ast, env);
	ast = NULL;
	temp = ft_calloc(3, sizeof(char *));
	temp[0] = ft_strdup(env->pwd);
	temp[1] = ft_strdup(env->oldpwd);
	temp[2] = NULL;
	ft_export(temp, &env);
	ft_free_double_array(temp);
	rl_replace_line("", 0);
	return (true);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
	test_sig = false;
	rl_outstream = stderr;
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
		signal(SIGINT, &sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGPIPE, SIG_IGN);
		if (!loop(env))
			continue ;
	}
	ft_exit(NULL, NULL, env, NULL);
}


// int	main(int ac , char **av)
// {	(void)ac;

// 	av++;
// 	ft_printf("%s\n", av[0]);
// 	ft_printf("-------------\n");
// 	av[1] = rem_wspace(av[0]);
// 	av = ft_split_arg(av[], ' ');
// 	ft_print_double_array(av);
// 	ft_free_double_array(av);
// }
