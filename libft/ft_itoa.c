/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 11:26:19 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:03:23 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		len;
	long	ln;
	char	*str;

	len = ft_intlen(n) + (n < 0);
	if (!(str = ft_strnew(len)))
		return (NULL);
	ln = (long)n * (n < 0 ? -1 : 1);
	if (n < 0)
		str[0] = '-';
	while (--len >= (n < 0))
	{
		str[len] = '0' + (ln % 10);
		ln /= 10;
	}
	return (str);
}
