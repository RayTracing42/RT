/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/07 14:35:45 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cylinder_intersect(t_ray *ray, t_parequation e,
	t_object *obj, int i)
{
	t_cylinder		*c;
	double			t;
	double			fac[3];

	c = (t_cylinder *)obj;
	t = -1;
	fac[_A] = pow(e.vd.x, 2) + pow(e.vd.z, 2);
	fac[_B] = 2 * (e.vd.x * e.vc.x + e.vd.z * e.vc.z);
	fac[_C] = pow(e.vc.x, 2) + pow(e.vc.z, 2) - c->r2;
	if ((ray->nb_intersect = get_quad_equation_sol(&t, fac, i)))
		ray->inter = equation_get_dot(&e, t);
	return (t);
}

static const t_vector	*get_cylinder_normal(t_dot *inter, t_object *obj)
{
	t_cylinder	*c;

	c = (t_cylinder *)obj;
	c->normal = (t_vector){2 * inter->x, 0, 2 * inter->z};
	return (&c->normal);
}

static int				is_in_cylinder(t_dot *i, t_object *obj)
{
	t_cylinder	*c;

	c = (t_cylinder *)obj;
	return ((pow(i->x, 2) + pow(i->z, 2) <= c->r2));
}

t_cylinder				*new_cylinder(t_objs_comp args, double radius)
{
	t_cylinder	*c;

	c = (t_cylinder *)new_object(CYLINDER, args);
	c->radius = radius;
	c->get_normal = get_cylinder_normal;
	c->is_in_obj = is_in_cylinder;
	c->intersect = cylinder_intersect;
	c->r2 = pow(radius, 2);
	return (c);
}

void					delete_cylinder(t_cylinder *cylinder)
{
	delete_object((t_object*)cylinder);
}
