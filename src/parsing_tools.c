/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:47:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/04 13:36:30 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		between(double value, double low_limit, double height_limit)
{
	if (value < low_limit || value > height_limit)
		return (-1);
	return (1);
}
/*
double	int_to_decimal(int n)
{
	double	d;

	d = (double)n;
	while (d > 1 || d < -1)
		d = d / 10;
	return (d);
}

double	atod(char *src)
{
	double	integer_part;
	double	decimal_part;
	int		tmp_decimal;

	decimal_part = 0.0;
	integer_part = (double)atoi(src);
	if (ft_strchr(src, '.'))
	{
		tmp_decimal = atoi((src + ft_strnlen(src, '.') + 1));
		decimal_part = int_to_decimal(tmp_decimal);
	}
	return (integer_part + decimal_part);
}
*/
double	atod(char *src)
{
	double	integer;
	double	decimal;
	char	*tmp;
	int		i;

	integer = abs(atoi(src));
	decimal = 0;
	if (ft_strchr(src, '.'))
	{
		i = 0;
		decimal = 1;
		ft_strncpy((tmp = ft_strnew(7)), ft_strchr(src, '.'), 7);
		while (*(tmp + (++i)))
			decimal *= 10;
		decimal = atoi(tmp + 1) / decimal;
		free(tmp);
	}
	return ((integer + decimal) * (*src == '-' ? -1 : 1));
}
