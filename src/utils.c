/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:25:07 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/08 17:36:57 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double		angle_between_vectors(t_vector a, t_vector b)
{
	double	angle;
	double	pdt_scalaire;
	double	dist_a;
	double	dist_b;

	dist_a = get_vect_lenght(&a);
	dist_b = get_vect_lenght(&b);
	if (!(dist_a && dist_b))
		return (0);
	pdt_scalaire = vect_dot_product(&a, &b);
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
