/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:33:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/16 11:27:42 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			sphere_intersect(t_ray *ray, t_parequation e,
	t_object *obj, int i)
{
	t_sphere		*s;
	double			t[4];

	s = (t_sphere*)obj;
	t[0] = -1;
	t[1] = pow(e.vd.x, 2) + pow(e.vd.y, 2) + pow(e.vd.z, 2);
	t[2] = 2 * (e.vd.x * e.vc.x + e.vd.y * e.vc.y + e.vd.z * e.vc.z);
	t[3] = pow(e.vc.x, 2) + pow(e.vc.y, 2) + pow(e.vc.z, 2) - s->r2;
	if ((ray->nb_intersect = get_quad_equation_sol(t, i)))
		ray->inter = equation_get_dot(&e, t[0]);
	return (t[0]);
}

static const t_vector	*get_sphere_normal(t_dot *inter, t_object *obj)
{
	t_sphere	*s;

	s = (t_sphere*)obj;
	s->normal = (t_vector){2 * inter->x, 2 * inter->y, 2 * inter->z};
	return (&s->normal);
}

static int				is_in_sphere(t_dot *i, t_object *obj)
{
	t_sphere	*s;

	s = (t_sphere*)obj;
	return ((pow(i->x, 2) + pow(i->y, 2) + pow(i->z, 2) <= s->r2));
}

t_sphere				*new_sphere(t_objs_comp args, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)new_object(SPHERE, args);
	sphere->radius = radius;
	sphere->get_normal = get_sphere_normal;
	sphere->is_in_obj = is_in_sphere;
	sphere->intersect = sphere_intersect;
	sphere->r2 = pow(radius, 2);
	return (sphere);
}

void					delete_sphere(t_sphere *sphere)
{
	delete_object((t_object*)sphere);
}
