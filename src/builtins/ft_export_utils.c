/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 15:08:21 by bchedru           #+#    #+#             */
/*   Updated: 2024/11/04 15:12:29 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	only_char(char	*str, char c)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] != c)
			return (false);
	return (true);
}

bool	export_error_handler(char	**temp, char	*error_message)
{
	ft_putstr_fd("export: ", STDERR_FILENO);
	ft_putstr_fd(error_message, STDERR_FILENO);
	ft_putstr_fd(temp[0], STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	ft_free_double_array(temp);
	return (false);
}
