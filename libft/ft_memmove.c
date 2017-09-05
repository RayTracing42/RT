/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:07:53 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:13:18 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	int				i;
	int				j;

	if (!dest || !src)
		return (NULL);
	i = (dest < src ? 0 : n - 1);
	j = (dest < src ? 1 : -1);
	while (n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i += j;
		--n;
	}
	return (dest);
}
