/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 12:55:37 by edescoin          #+#    #+#             */
/*   Updated: 2016/12/03 14:33:39 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_digit(char c, int base)
{
	if (!(ft_memchr("0123456789abcdefghijklmnopqrstuvwxyz", c, base)))
	{
		if (!(ft_memchr("0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", c, base)))
			return (-1);
		else
			return (ft_isdigit(c) ? c - '0' : 10 + (c - 'A'));
	}
	else
		return (ft_isdigit(c) ? c - '0' : 10 + (c - 'a'));
}

int			ft_atoi_base(const char *nptr, int base)
{
	long	i;
	long	nb;
	int		dt;
	int		j;

	if (!nptr || !base)
		return (0);
	i = 0;
	nb = 0;
	while (ft_isspace(nptr[i]) && nptr[i])
		i++;
	if (!nptr[i])
		return (0);
	if (nptr[i] == '+' || nptr[i] == '-')
		++i;
	while (get_digit(nptr[i], base) > -1)
		++i;
	j = -1;
	while (--i >= 0 && (dt = get_digit(nptr[i], base)) > -1)
		nb = nb + (dt * (ft_pow(base, ++j)));
	return ((int)(dt == -1 && nptr[i] == '-' ? -nb : nb));
}
