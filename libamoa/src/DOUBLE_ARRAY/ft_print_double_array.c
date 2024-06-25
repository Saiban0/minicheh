/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_double_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 20:15:46 by bchedru           #+#    #+#             */
/*   Updated: 2024/06/25 20:19:02 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

void	ft_print_double_array(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		ft_printf("%s\n", str[i]);
}
