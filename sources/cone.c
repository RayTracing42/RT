/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:05:50 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 15:08:27 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cone_intersect(t_ray *ray, t_cone *c)
{
	t_vector	*vd;
	t_vector	vc;
	double		t;

	vc = vector(ray->equ.vc.x - c->origin.x, ray->equ.vc.y - c->origin.y,
			ray->equ.vc.z - c->origin.z);
	vd = &ray->equ.vd;
	if ((t = delta(pow(vd->x, 2) + pow(vd->z, 2) - pow(vd->y, 2) * c->tanalpha2,
			2 * (vd->x * vc.x + vd->z * vc.z - vd->y * vc.y * c->tanalpha2),
			pow(vc.x, 2) + pow(vc.z, 2) - pow(vc.y, 2) * c->tanalpha2)))
	{
		ray->inter = dot(ray->equ.vc.x + vd->x * t, ray->equ.vc.y + vd->y * t,
				ray->equ.vc.z + vd->z * t);
		return (t);
	}
	return (-1);
}

static const t_vector	*get_cone_normal(t_dot *d, t_cone *c)
{
	(void)d;
	//set_vector(&c->normal, 2 * d->x, -2 * c->tanalpha2 * d->y, 2 * d->z);
	return (&c->normal);
}

t_cone					*new_cone(t_objs_comp args, double angle,
								double height_top, double height_bottom)
{
	t_cone	*c;

	c = (t_cone*)new_object(CONE, args.origin, args.dir, args.color);
	c->angle = angle;
	c->height_top = height_top;
	c->height_bottom = height_bottom;
	c->get_normal = get_cone_normal;
	c->intersect = cone_intersect;
	c->tanalpha2 = pow(tan(angle * M_PI / 180), 2);
	return (c);
}

void					delete_cone(t_cone *cone)
{
	delete_object((t_object*)cone);
}
