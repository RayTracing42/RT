/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:33:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 15:12:27 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			sphere_intersect(t_ray *ray, t_sphere *s)
{
	t_vector	*vd;
	t_vector	vc;
	double		t;

	vc = vector(ray->equ.vc.x - s->origin.x, ray->equ.vc.y - s->origin.y,
			ray->equ.vc.z - s->origin.z);
	vd = &ray->equ.vd;
	if ((t = delta(pow(vd->x, 2) + pow(vd->y, 2) + pow(vd->z, 2),
		2 * (vd->x * vc.x + vd->y * vc.y + vd->z * vc.z),
		pow(vc.x, 2) + pow(vc.y, 2) + pow(vc.z, 2) - s->r2)))
	{
		ray->inter = dot(ray->equ.vc.x + vd->x * t, ray->equ.vc.y + vd->y * t,
				ray->equ.vc.z + vd->z * t);
		return (t);
	}
	return (-1);
}

static const t_vector	*get_sphere_normal(t_dot *d, t_sphere *s)
{
	s->normal = (t_vector){2 * (d->x - s->origin.x), 2 * (d->y - s->origin.y), 2 * (d->z - s->origin.z)};
	return (&s->normal);
}

t_sphere				*new_sphere(t_objs_comp args, double radius)
{
	t_sphere	*sphere;

	sphere = (t_sphere*)new_object(SPHERE, args.origin, args.dir, args.color);
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
