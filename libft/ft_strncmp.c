/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 18:21:16 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:23:44 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;

	if (!s1 || !s2)
		return (0);
	c1 = *s1;
	c2 = *s2;
	if (c1 && c2 && n > 1)
		return (c1 == c2 ? ft_strncmp(s1 + 1, s2 + 1, n - 1) : (c1 - c2));
	return (!n ? 0 : c1 - c2);
}
