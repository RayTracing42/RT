/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:16:14 by shiro             #+#    #+#             */
/*   Updated: 2018/01/08 17:34:16 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			triangle_intersect(t_ray *ray, t_parequation e,
	t_object *obj, int i)
{
		double		t;
		double		denom;
		double		tmp;
		t_triangle	*tgl;
		t_dot		dtmp;

		(void)i;
		t = -1;
		ray->nb_intersect = 0;
		tgl = (t_triangle*)obj;
		if (!(denom = tgl->a * e.vd.x + tgl->b * e.vd.y + tgl->c * e.vd.z))
			return (-1);
		t = -((tgl->a * e.vc.x + tgl->b * e.vc.y + tgl->c * e.vc.z + tgl->d) / denom);
		if (gt(t, 0))
		{
			ray->inter = equation_get_dot(&e, t);
			dtmp = (t_dot){ray->inter.x + tgl->origin.x, ray->inter.y + tgl->origin.y, ray->inter.z + tgl->origin.z};
			if (gt(tmp = angle_between_vectors(tgl->vAB, dots_to_vect(tgl->dA, dtmp)), tgl->aA))
				t = -1;
			else if (gt(tmp = angle_between_vectors(tgl->vBA, dots_to_vect(tgl->dB, dtmp)), tgl->aB))
				t = -1;
			else if (gt(tmp = angle_between_vectors(tgl->vBC, dots_to_vect(tgl->dB, dtmp)), tgl->aB))
				t = -1;
			else
				ray->nb_intersect = 2;
		}
		return (t);
}

t_triangle	*new_triangle(t_objs_comp args, t_dot dA, t_dot dB, t_dot dC)
{
	t_triangle	*triangle;

	triangle = (t_triangle*)new_plane(args, vect_cross_product(dots_to_vect(dA, dB), dots_to_vect(dA, dC)), 1);
	triangle->vAB = dots_to_vect(dA, dB);
	triangle->vBA = dots_to_vect(dB, dA);
	triangle->vBC = dots_to_vect(dB, dC);
	triangle->aA = fabs(angle_between_vectors(triangle->vAB, dots_to_vect(dA, dC)));
	triangle->aB = fabs(angle_between_vectors(triangle->vBA, dots_to_vect(dB, dC)));
	triangle->dA = dA;
	triangle->dB = dB;
	triangle->dC = dC;
	//(void)triangle_intersect;
	triangle->intersect = &triangle_intersect;
	return (triangle);
}

void		delete_triangle(t_triangle	*triangle)
{
	delete_plane((t_plane*)triangle);
}
