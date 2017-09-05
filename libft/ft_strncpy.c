/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:46:44 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:24:26 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t	i;
	size_t	src_len;

	if (!dst)
		return (NULL);
	if (src)
	{
		src_len = ft_strlen(src);
		i = -1;
		while (++i < len)
			dst[i] = (i >= src_len) ? '\0' : src[i];
	}
	return (dst);
}
