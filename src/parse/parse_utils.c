/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:08 by tom               #+#    #+#             */
/*   Updated: 2024/10/18 14:09:30 by tom              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rem_wspace(char *command)
{
	int	i;

	i = 0;
	while(is_whitespace(command[i]))
		command++;
	i = ft_strlen(command);
	while(is_whitespace(command[i--]))
		continue;
	if (is_whitespace(command[i]))
		command[i] = '\0';
	return (command);
}

void	quote_handler(char	*line, t_env	**env, int	quote_pos)
{
	if ((*env)->quote == 0)
		{(*env)->quote = line[quote_pos];ft_printf("quote open\n");}
	else if ((*env)->quote == line[quote_pos])
		{(*env)->quote = 0;ft_printf("quote close\n");}
	else if ((*env)->quote != 0 && (*env)->quote != line[quote_pos])
		return ;
	return ;
}
