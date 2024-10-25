/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:09:02 by tom               #+#    #+#             */
/*   Updated: 2024/10/25 16:02:14 by tom              ###   ########.fr       */
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
		write(STDERR_FILENO, "\n", 1);
		test_sig = true;
		// exit(0);
	}
}

bool	loop(t_env	*env)
{
	char	*line;
	t_ast	*ast;
	char	**temp;

	line = get_next_line(0);
	if (test_sig == true)
		{test_sig = false;ft_exit(line, NULL, env);exit(0);}
	if (line[0] == '\n')
		return (false);
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
	// exec_switch(ast, env);
	ft_print_double_array(ast->base->cmd);
	free_ast(ast);
	ast = NULL;
	temp = ft_calloc(3, sizeof(char *));
	temp[0] = ft_strdup(env->pwd);
	temp[1] = ft_strdup(env->oldpwd);
	temp[2] = NULL;
	ft_export(temp, &env);
	ft_free_double_array(temp);
	return (true);
}

int main(int ac, char **av, char **envp)
{

	t_env	*env;

	(void)av;
	test_sig = false;
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
			continue;
	}
	ft_free_double_array(env->envv);
	free(env);
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
