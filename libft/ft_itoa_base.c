/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:26:19 by edescoin          #+#    #+#             */
/*   Updated: 2016/12/15 17:46:43 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char	get_char(int i, int base)
{
	if (i >= base || i > 35)
		return (0);
	return ("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"[i]);
}

static char	*create_string(char *str, long l, int base)
{
	int	d;
	int	m;

	d = l / base;
	m = l % base;
	ft_strrealloc(str, ft_strlen(str) + 1);
	if (d < base)
	{
		*str = get_char(d, base);
		*(++str) = get_char(m, base);
		return (str + 1);
	}
	str = create_string(str, (long)d, base);
	*str = get_char(m, base);
	return (str + 1);
}

char		*ft_itoa_base(int n, int base)
{
	long	ln;
	char	*str;

	if (!(str = ft_strnew(2)))
		return (NULL);
	ln = (long)n * (n < 0 ? -1 : 1);
	if (n < 0)
	{
		str[0] = '-';
		str = ft_strrealloc(str, 3);
	}
	create_string(str, ln, base);
	return (str);
}
