/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:16:14 by shiro             #+#    #+#             */
/*   Updated: 2018/01/08 17:50:16 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double			triangle_intersect(t_ray *ray, t_parequation e,
	t_object *obj, int i)
{
	double		t;
	double		tmp;
	t_triangle	*tgl;
	t_dot		itmp;

	tgl = (t_triangle*)obj;
	if (gt(t = plane_intersect(ray, e, obj, i), 0))
	{
		itmp = (t_dot){ray->inter.x + tgl->origin.x, ray->inter.y + tgl->origin.y, ray->inter.z + tgl->origin.z};
		if (gt(tmp = angle_between_vectors(tgl->vAB, dots_to_vect(tgl->dA, itmp)), tgl->aA))
			t = -1;
		else if (gt(tmp = angle_between_vectors(tgl->vBA, dots_to_vect(tgl->dB, itmp)), tgl->aB))
			t = -1;
		else if (gt(tmp = angle_between_vectors(tgl->vBC, dots_to_vect(tgl->dB, itmp)), tgl->aB))
			t = -1;
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
	triangle->intersect = &triangle_intersect;
	return (triangle);
}

void		delete_triangle(t_triangle	*triangle)
{
	delete_plane((t_plane*)triangle);
}
