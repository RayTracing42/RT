/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:33:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/13 16:36:06 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			sphere_intersect(int *nbi, t_dot *dst, t_parequation e, t_object *obj)
{
	t_sphere	*s;
	double		t;

	t = -1;
	s = (t_sphere*)obj;
	if ((*nbi = get_quad_equation_sol(&t,
				pow(e.vd.x, 2) + pow(e.vd.y, 2) + pow(e.vd.z, 2),
				2 * (e.vd.x * e.vc.x + e.vd.y * e.vc.y + e.vd.z * e.vc.z),
				pow(e.vc.x, 2) + pow(e.vc.y, 2) + pow(e.vc.z, 2) - s->r2)))
		*dst = equation_get_dot(&e, t);
	return (t);
}

static const t_vector	*get_sphere_normal(t_dot *inter, t_object *obj)
{
	t_sphere	*s;

	s = (t_sphere*)obj;
	s->normal = (t_vector){2 * inter->x, 2 * inter->y, 2 * inter->z};
	return (&s->normal);
}

t_sphere				*new_sphere(t_objs_comp args, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)new_object(SPHERE, args);
	sphere->radius = radius;
	sphere->get_normal = get_sphere_normal;
	sphere->intersect = sphere_intersect;
	sphere->r2 = pow(radius, 2);
	return (sphere);
}

void					delete_sphere(t_sphere *sphere)
{
	delete_object((t_object*)sphere);
}
