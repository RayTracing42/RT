/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 13:19:48 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:26:34 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fd_str(const char *s1, const char *s2)
{
	if (*s1 == *s2)
	{
		if (*(s1 + 1) && *(s2 + 1))
			return (fd_str(s1 + 1, s2 + 1) ? (char*)s1 : NULL);
		return ((char*)s1);
	}
	return (NULL);
}

char		*ft_strnstr(const char *big, const char *little, size_t len)
{
	if ((big && little && ft_strlen(little) > len) || !big || !little)
		return (NULL);
	if (!(*little))
		return ((char*)big);
	if (*big)
	{
		return (fd_str(big, little) ? (char*)big :
		ft_strnstr(big + 1, little, len - 1));
	}
	return (NULL);
}
