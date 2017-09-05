/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/08 16:04:52 by edescoin          #+#    #+#             */
/*   Updated: 2016/11/24 12:01:47 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	long	i;
	long	nb;
	int		sign;

	if (!nptr)
		return (0);
	i = 0;
	nb = 0;
	sign = 1;
	while (ft_isspace(nptr[i]) && nptr[i])
		i++;
	if (!nptr[i])
		return (0);
	if (nptr[i] == '+' || nptr[i] == '-')
		sign = (nptr[i] == '+' ? 1 : -1);
	else
		--i;
	while (ft_isdigit(nptr[++i]))
		nb = nb * 10 + (nptr[i] - '0');
	return ((int)(sign * nb));
}
