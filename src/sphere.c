/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:33:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 19:53:52 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			sphere_intersect(t_ray *ray, t_sphere *s)
{
	return (0);
	t_dot		res;
	t_vector	*vd;
	t_vector	*vc;
	double		t;

	t = -1;
	vc = &ray->equ.vc;
	vd = &ray->equ.vd;
	if (get_quad_equation_sol(&res,
			pow(vd->x, 2) + pow(vd->y, 2) + pow(vd->z, 2),
			2 * (vd->x * vc->x + vd->y * vc->y + vd->z * vc->z),
			pow(vc->x, 2) + pow(vc->y, 2) + pow(vc->z, 2) - s->r2))
	{
		if ((long)(res.x * pow(10, 12)) > 0)
		{
			if ((long)(res.y * pow(10, 12)) > 0)
				t = (res.x < res.y ? res.x : res.y);
			else
				t = (res.x);
		}
		else if ((long)(res.y * pow(10, 12)) > 0)
			t = (res.y);
	}
	return (t);
}

static const t_vector	*get_sphere_normal(t_dot *d, t_sphere *s)
{
	(void)d;
	//set_vector(&s->normal, 2 * d->x, 2 * d->y, 2 * d->z);
	return (&s->normal);
}

t_sphere				*new_sphere(t_objs_comp args, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)new_object(SPHERE, args.orig, args.dir, args.col);
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
