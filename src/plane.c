/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:35:04 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/21 16:48:44 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			plane_intersect(int *nbi, t_dot *dst, t_parequation e, t_object *obj)
{
	double		t;
	double		denom;
	t_plane		*p;

	t = -1;
	*nbi = 0;
	p = (t_plane*)obj;
	if (!(denom = p->a * e.vd.x + p->b * e.vd.y + p->c * e.vd.z))
		return (-1);
	t = -((p->a * e.vc.x + p->b * e.vc.y + p->c * e.vc.z + p->d) / denom);
	if (gt(t, 0))
	{
		*nbi = 1;
		*dst = equation_get_dot(&e, t);
	}
	return (t);
}

static const t_vector	*get_plane_normal(t_dot *inter, t_object *obj)
{
	(void)inter;
	return (&obj->normal);
}

int						is_in_plane(t_dot *d, t_plane *p)
{
	double	res;

	res = p->a * d->x + p->b * d->y + p->c * d->z + p->d;
	res *= pow(10, 12);
	return (!((long)res > 0 || (long)res < 0));
}

t_plane					*new_plane(t_objs_comp args, t_vector normal)
{
	t_plane		*plane;

	plane = (t_plane*)new_object(PLANE, args);
	plane->normal = normal;
	plane->get_normal = get_plane_normal;
	plane->intersect = plane_intersect;
	plane->a = normal.x;
	plane->b = normal.y;
	plane->c = normal.z;
/*	plane->d = -(normal.x * args.orig.x + normal.y * args.orig.y + normal.z * args.orig.z);*/
	plane->d = 0;
	plane->z = args.orig.z;
	return (plane);
}

void					delete_plane(t_plane *plane)
{
	delete_object((t_object*)plane);
}
