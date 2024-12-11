/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:09:02 by tom               #+#    #+#             */
/*   Updated: 2024/12/11 16:48:11 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile int	g_exit_code = 0;

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

static void	handle_envp_false(char **temp, t_env *env)
{
	temp = ft_calloc(3, sizeof(char *));
	if (env->pwd_position != -1)
		temp[0] = ft_strdup(env->pwd);
	if (env->oldpwd_position != -1)
		temp[1] = ft_strdup(env->oldpwd);
	temp[2] = NULL;
	if (env->pwd_position != -1 && env->oldpwd_position != -1)
		ft_export(temp, &env);
}

static void	loop_bis(char *line, t_ast *ast, t_env *env)
{
	char	**temp;

	if (parse(line, &ast, env, 0) == false)
	{
		free(line);
		if (ast)
			free_ast(ast);
		return ;
	}
	free(line);
	line = NULL;
	g_exit_code = 0;
	exec_switch(ast, env);
	ast = NULL;
	temp = NULL;
	if (env->envp == false)
		handle_envp_false(temp, env);
	ft_free_double_array(temp);
	rl_replace_line("", 0);
}

bool	loop(t_env *env)
{
	char	*line;
	t_ast	*ast;

	line = readline("minicheh-> ");
	if (!line)
	{
		ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_exit(NULL, NULL, env, NULL);
	}
	if (line[0] == '\0')
		return (false);
	add_history(line);
	if (only_wspace(line))
	{
		free(line);
		return (false);
	}
	ast = ft_calloc(1, sizeof(t_ast) + 1);
	ast->base = ft_calloc(1, sizeof(t_ast_content) + 1);
	env->nb_commands = 0;
	loop_bis(line, ast, env);
	return (true);
}

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)av;
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
		if (!loop(env))
			continue ;
	}
	ft_exit(NULL, NULL, env, NULL);
}
