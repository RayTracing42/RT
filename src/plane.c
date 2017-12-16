/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:35:04 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/16 09:44:14 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			plane_intersect(t_ray *ray, t_parequation e, t_object *obj, int i)
{
	double			t;
	double			denom;
	t_plane			*p;

	(void)i;
	t = -1;
	ray->nb_intersect = 0;
	p = (t_plane*)obj;
	if (!(denom = p->a * e.vd.x + p->b * e.vd.y + p->c * e.vd.z))
		return (-1);
	t = -((p->a * e.vc.x + p->b * e.vc.y + p->c * e.vc.z + p->d) / denom);
	if (gt(t, 0))
	{
		ray->nb_intersect = 1;
		ray->inter = equation_get_dot(&e, t);
	}
	return (t);
}

static const t_vector	*get_plane_normal(t_dot *inter, t_object *obj)
{
	(void)inter;
	return (&obj->normal);
}

static int				is_in_plane(t_dot *i, t_object *obj)
{
	double	res;
	t_plane *p;

	p = (t_plane *)obj;
	res = p->a * i->x + p->b * i->y + p->c * i->z + p->d;
	res *= pow(10, 12);
	return (!((long)res > 0 || (long)res < 0));
}

t_plane					*new_plane(t_objs_comp args, t_vector normal)
{
	t_plane		*plane;

	plane = (t_plane*)new_object(PLANE, args);
	plane->normal = normal;
	plane->get_normal = get_plane_normal;
	plane->is_in_obj = is_in_plane;
	plane->intersect = plane_intersect;
	plane->a = normal.x;
	plane->b = normal.y;
	plane->c = normal.z;
	plane->d = 0;
	plane->z = args.orig.z;
	return (plane);
}

void					delete_plane(t_plane *plane)
{
	delete_object((t_object*)plane);
}
