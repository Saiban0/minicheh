/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:49:58 by ttaquet           #+#    #+#             */
/*   Updated: 2024/05/07 17:20:28 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

void	ft_free_double_array(char **double_array)
{
	int	i;

	i = -1;
	if (!double_array)
		return ;
	while (double_array[++i])
		free(double_array[i]);
	free(double_array);
}
