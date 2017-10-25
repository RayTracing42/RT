/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:05:50 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 17:02:06 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cone_intersection(t_ray *ray, t_object *obj)
{
	t_cone		*c;
	t_vector	*vd;
	t_vector	vc;
	double		t;

	c = (t_cone*)obj;
	vc = vector(ray->equ.vc.x - c->origin.x, ray->equ.vc.y - c->origin.y,
			ray->equ.vc.z - c->origin.z);
	vd = &ray->equ.vd;
	t = delta(pow(vd->x, 2) + pow(vd->z, 2) - pow(vd->y, 2) * c->tanalpha2,
			2 * (vd->x * vc.x + vd->z * vc.z - vd->y * vc.y * c->tanalpha2),
			pow(vc.x, 2) + pow(vc.z, 2) - pow(vc.y, 2) * c->tanalpha2);
	if ((long)(t * pow(10, 12)) > 0)
	{
		ray->inter = dot(ray->equ.vc.x + vd->x * t, ray->equ.vc.y + vd->y * t,
				ray->equ.vc.z + vd->z * t);
		return (t);
	}
	return (-1);
}

static const t_vector	*get_cone_normal(t_dot *inter, t_object *obj)
{
	t_cone	*c;

	c = (t_cone*)obj;
	c->normal = (t_vector){2 * (inter->x - c->origin.x),
								-2 * c->tanalpha2 * (inter->y - c->origin.y),
								2 * (inter->z - c->origin.z)};
	return (&c->normal);
}

t_cone					*new_cone(t_objs_comp args, double angle,
								double height_top, double height_bottom)
{
	t_cone	*c;

	c = (t_cone*)new_object(CONE, args);
	c->angle = angle;
	c->height_top = height_top;
	c->height_bottom = height_bottom;
	c->get_normal = get_cone_normal;
	c->intersect = cone_intersection;
	c->tanalpha2 = pow(tan(angle * M_PI / 180), 2);
	return (c);
}

void					delete_cone(t_cone *cone)
{
	delete_object((t_object*)cone);
}
