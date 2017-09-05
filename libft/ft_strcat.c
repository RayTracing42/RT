/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 19:17:51 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:16:52 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat(char *s1, const char *s2)
{
	long	i;
	long	j;

	if (!s1)
		return (NULL);
	if (s2)
	{
		i = -1;
		j = ft_strlen(s1) - 1;
		while (s2[++i])
			s1[++j] = s2[i];
		s1[j + 1] = '\0';
	}
	return (s1);
}
