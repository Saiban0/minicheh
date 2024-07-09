/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tom <tom@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 18:30:08 by tom               #+#    #+#             */
/*   Updated: 2024/06/30 18:10:52 by tom              ###   ########.fr       */
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
	if (is_whitespace(command[i]))
	{
		while(is_whitespace(command[--i]))
			continue;
		command[i] = '\0';
	}
	return (command);
}
