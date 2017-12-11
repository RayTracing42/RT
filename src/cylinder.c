/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/11 17:11:18 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cylinder_intersect(int *nbi, t_dot *dst, t_parequation e, t_object *obj)
{
	t_cylinder	*c;
	double		t;

	t = -1;
	c = (t_cylinder*)obj;
	if ((*nbi = get_quad_equation_sol(&t, pow(e.vd.x, 2) + pow(e.vd.z, 2),
									2 * (e.vd.x * e.vc.x + e.vd.z * e.vc.z),
									pow(e.vc.x, 2) + pow(e.vc.z, 2) - c->r2)))
		*dst = equation_get_dot(&e, t);
	return (t);
}

static const t_vector	*get_cylinder_normal(t_dot *inter, t_object *obj)
{
	t_cylinder	*c;

	c = (t_cylinder*)obj;
	c->normal =  (t_vector){2 * inter->x, 0, 2 * inter->z};
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
