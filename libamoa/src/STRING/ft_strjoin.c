/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttaquet <ttaquet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 16:31:23 by ttaquet           #+#    #+#             */
/*   Updated: 2024/02/23 14:46:16 by ttaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

char	*ft_strjoin(char *s1, char *s2, int nb_free)
{
	char			*joinedstr;
	int				i;
	int				j;
	unsigned int	tmp;

	i = -1;
	j = -1;
	tmp = (unsigned int)(ft_strlen(s1) + ft_strlen(s2));
	joinedstr = malloc((tmp + 1) * sizeof(char));
	if (!joinedstr)
		return (NULL);
	while (s1[++j])
		joinedstr[++i] = s1[j];
	j = -1;
	while (s2[++j])
		joinedstr[++i] = s2[j];
	if (nb_free > 0)
		free(s1);
	if (nb_free > 1)
		free(s2);
	joinedstr[++i] = '\0';
	return (joinedstr);
}
