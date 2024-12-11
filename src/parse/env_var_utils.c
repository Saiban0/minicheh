/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 14:32:49 by ttaquet           #+#    #+#             */
/*   Updated: 2024/12/09 14:33:11 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		else if ((is_whitespace(temp[i]) || temp[i] == '\'' || temp[i] == '"')
			&& env_var == true)
		{
			env_var = false;
			res++;
		}
	}
	free(temp);
	return (res);
}
