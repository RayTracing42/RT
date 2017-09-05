/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 16:31:49 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:20:16 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	long	i;
	long	len;
	char	*str;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	if (!(str = (char*)malloc(len + 1)))
		return (NULL);
	i = -1;
	while (++i < len)
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}
