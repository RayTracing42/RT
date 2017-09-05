/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 18:15:11 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:11:47 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (!n || !s)
		return (NULL);
	if (n > 1 && *(unsigned char*)s != (unsigned char)c)
		return (ft_memchr(s + 1, c, n - 1));
	return (*(unsigned char*)s == (unsigned char)c ? (void*)s : NULL);
}
