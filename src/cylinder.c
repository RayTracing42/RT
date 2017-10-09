/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/09 16:59:47 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cylinder_intersect(t_ray *ray, t_object *obj)
{
	(void)obj;
	(void)ray;
	return (0);
	/*t_dot		res;
	t_vector	*vd;
	t_vector	*vc;
	double		t;

	t = -1;
	vc = &ray->eq_obj.vconst;
	vd = &ray->eq_obj.vdir;
	if (get_quad_equation_sol(&res, pow(vd->x, 2) + pow(vd->z, 2),
							2 * (vd->x * vc->x + vd->z * vc->z),
							pow(vc->x, 2) + pow(vc->z, 2) - c->r2))
	{
		if ((long)(res.x * pow(10, 12)) > 0 && in_boundary(ray, c, res.x))
		{
			if ((long)(res.y * pow(10, 12)) > 0 && in_boundary(ray, c, res.y))
				t = (res.x < res.y ? res.x : res.y);
			else
				t = (res.x);
		}
		else if ((long)(res.y * pow(10, 12)) > 0 && in_boundary(ray, c, res.y))
			t = (res.y);
	}
	return (t);*/
}

static const t_vector	*get_cylinder_normal(t_dot *inter, t_object *obj)
{
	//set_vector(&c->normal, 2 * d->x, 0, 2 * d->z);
	(void)inter;
	return (&obj->normal);
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
	//c->r2 = pow(radius, 2);
	return (c);
}

void					delete_cylinder(t_cylinder *cylinder)
{
	delete_object((t_object*)cylinder);
}
