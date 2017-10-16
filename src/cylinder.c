/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/16 18:08:19 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cylinder_intersect(t_ray *ray, t_object *obj)
{
	t_cylinder	*c;
	t_vector	*vd;
	t_vector	vc;
	double		t;

	c = (t_cylinder*)obj;
	vc = vector(ray->equ.vc.x - c->origin.x, ray->equ.vc.y - c->origin.y,
			ray->equ.vc.z - c->origin.z);
	vd = &ray->equ.vd;
	if ((t = delta(pow(vd->x, 2) + pow(vd->z, 2),
			2 * (vd->x * vc.x + vd->z * vc.z),
			pow(vc.x, 2) + pow(vc.z, 2) - c->r2)))
	{
		ray->inter = dot(ray->equ.vc.x + vd->x * t, ray->equ.vc.y + vd->y * t,
				ray->equ.vc.z + vd->z * t);
		return (t);
	}
	return (-1);
}

static const t_vector	*get_cylinder_normal(t_dot *inter, t_object *obj)
{
	t_cylinder	*c;

	c = (t_cylinder*)obj;
	c->normal =  (t_vector){2 * (inter->x - c->origin.x), 0, 2 * (inter->z - c->origin.z)};
	return (&c->normal);
}

t_cylinder				*new_cylinder(t_objs_comp args, double radius,
									double height_top, double height_bottom)
{
	t_cylinder	*c;

	c = (t_cylinder*)new_object(CYLINDER, args);
	c->radius = radius;
	c->height_top = height_top;
	c->height_bottom = height_bottom;
	c->get_normal = get_cylinder_normal;
	c->intersect = cylinder_intersect;
	c->r2 = pow(radius, 2);
	return (c);
}

void					delete_cylinder(t_cylinder *cylinder)
{
	delete_object((t_object*)cylinder);
}
