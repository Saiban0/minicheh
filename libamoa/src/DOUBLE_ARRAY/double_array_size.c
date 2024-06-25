/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_array_size.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 17:15:03 by ttaquet           #+#    #+#             */
/*   Updated: 2024/04/10 17:33:20 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	double_array_size(char **double_array)
{
	int	size;

	size = -1;
	while (double_array[++size])
		continue ;
	return (size);
}
