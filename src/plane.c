/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:35:04 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 17:03:10 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			plane_intersect(t_ray *ray, t_object *obj)
{
	t_vector	*vd;
	t_vector	vc;
	double		t;
	double		denom;
	t_plane		*p;

	p = (t_plane*)obj;
	vc = (t_vector){ray->equ.vc.x - p->origin.x, ray->equ.vc.y - p->origin.y,
					ray->equ.vc.z - p->origin.z};
	vd = &ray->equ.vd;
	denom = (p->normal.x * vd->x + p->normal.y * vd->y + p->normal.z * vd->z);
	if (!denom)
		return (-1);
	t = -((p->normal.x * vc.x + p->normal.y * vc.y + p->normal.z * vc.z + 0) /
		denom);
	if ((long)(t * pow(10, 12)) > 0)
	{
		ray->inter = dot(ray->equ.vc.x + vd->x * t, ray->equ.vc.y + vd->y * t,
				ray->equ.vc.z + vd->z * t);
		return (t);
	}
	return (-1);
}

static const t_vector	*get_plane_normal(t_dot *inter, t_object *obj)
{
	(void)inter;
	return (&obj->normal);
}

/*int						is_in_plane(t_dot *d, t_plane *p)
{
}*/

t_plane					*new_plane(t_objs_comp args, t_vector normal)
{
	t_plane		*plane;

	plane = (t_plane*)new_object(PLANE, args);
	plane->normal = normal;
	plane->get_normal = get_plane_normal;
	plane->intersect = plane_intersect;
	return (plane);
}

void					delete_plane(t_plane *plane)
{
	delete_object((t_object*)plane);
}
