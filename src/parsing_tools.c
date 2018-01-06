/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:47:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/06 02:32:42 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	get_interval() retourne l'intervalle alloué entre deux strings valides;
**	Retourne NULL si l'un des parametres n'est pas valide;
**	Retourne NULL si l'intervalle est inexistant : "";
**	Retourne NULL si start et stop ne sont pas trouvés dans src;
*/

int		between(double value, double low_limit, double height_limit)
{
	if (value < low_limit || value > height_limit)
		return (-1);
	return (1);
}

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
