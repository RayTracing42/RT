/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 12:37:28 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/30 12:56:37 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	long	i;
	long	j;
	char	*rev;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i])
		++i;
	if (!(rev = ft_strnew(i + 1)))
		return (NULL);
	j = -1;
	while ((--i) >= 0)
		rev[++j] = s[i];
	return (rev);
}
