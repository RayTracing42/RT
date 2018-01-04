/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:25:07 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/04 00:21:07 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		angle_between_vectors(t_vector a, t_vector b)
{
	double	angle;
	double	pdt_scalaire;
	double	dist_a;
	double	dist_b;

	dist_a = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	dist_b = sqrt(pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2));
	if (!(dist_a && dist_b))
		return (0);
	pdt_scalaire = (a.x * b.x + a.y * b.y + a.z * b.z);
	angle = acos(pdt_scalaire / (dist_a * dist_b)) * 180 / M_PI;
	return (angle);
}

/*
**	Si tu viens a rejouter negatif un jour, pense aux limites a faire gaffe
**	car elles pourraient buger avec ce status
*/

int			get_status(char *status)
{
	if (ft_strcmp("empty", status) == 0)
		return (0);
	else if (ft_strcmp("full", status) == 0)
		return (1);
	else if (ft_strcmp("negative", status) == 0)
		return (2);
	else if (ft_strcmp("none", status) == 0)
		return (3);
	else
		return (-1);
}

t_vector	vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_dot		dot(double x, double y, double z)
{
	t_dot	d;

	d.x = x;
	d.y = y;
	d.z = z;
	return (d);
}
