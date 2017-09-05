/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 17:25:08 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:23:21 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	long	i;
	long	j;

	if (!s1)
		return (NULL);
	if (s2)
	{
		i = -1;
		j = ft_strlen(s1) - 1;
		while (s2[++i] && i < (long)n)
			s1[++j] = s2[i];
		s1[j + 1] = '\0';
	}
	return (s1);
}
