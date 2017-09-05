/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:38:39 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:19:43 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcpy(char *dst, const char *src)
{
	long	i;

	if (!dst)
		return (NULL);
	if (src)
	{
		i = -1;
		while (src[++i])
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (dst);
}
