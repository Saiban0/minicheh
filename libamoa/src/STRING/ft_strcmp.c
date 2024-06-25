/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:00:49 by ttaquet           #+#    #+#             */
/*   Updated: 2024/05/07 17:19:39 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

int	ft_strcmp(char *first, char *second)
{
	int	i;

	i = -1;
	while (first[++i] && second[i])
		if (first[i] != second[i])
			return (((unsigned char)first[i]) - ((unsigned char)second[i]));
	return (((unsigned char)first[i]) - ((unsigned char)second[i]));
}
