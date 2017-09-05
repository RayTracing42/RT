/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:26:09 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/22 17:25:16 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	get_trim_size(char const *s)
{
	long	i;
	long	len;

	i = -1;
	len = ft_strlen(s);
	while (ft_isspace(s[++i]) && s[i] != '\0')
		--len;
	if (s[i] == '\0')
		return (0);
	i = ft_strlen(s);
	while (ft_isspace(s[--i]))
		--len;
	return (len);
}

char		*ft_strtrim(char const *s)
{
	long	len;
	long	i;
	long	j;
	char	*str;

	if (!s)
		return (NULL);
	len = get_trim_size(s);
	if (!(str = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (ft_isspace(s[i]))
		++i;
	j = -1;
	--i;
	while (++j < len)
		str[j] = s[++i];
	str[j] = '\0';
	return (str);
}
