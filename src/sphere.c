/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:33:37 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/06 17:19:11 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			sphere_intersect(t_ray *ray, t_parequation e,
	t_object *obj, int i)
{
	t_sphere		*s;
	double			t;
	double			fac[3];

	double u,v;

	s = (t_sphere*)obj;
	t = -1;
	fac[_A] = pow(e.vd.x, 2) + pow(e.vd.y, 2) + pow(e.vd.z, 2);
	fac[_B] = 2 * (e.vd.x * e.vc.x + e.vd.y * e.vc.y + e.vd.z * e.vc.z);
	fac[_C] = pow(e.vc.x, 2) + pow(e.vc.y, 2) + pow(e.vc.z, 2) - s->r2;
	if ((ray->nb_intersect = get_quad_equation_sol(&t, fac, i)))
		ray->inter = equation_get_dot(&e, t);

/*
	u = 0.5 + ft_to_deg(atan2(ray->inter.z, ray->inter.x)) / (2 * M_PI);
	v = 0.5 - ft_to_deg(asin(ray->inter.y)) / M_PI;
	s->color.r = (int)u % 255;
*/

	u = acos(ray->inter.y / s->radius);
	v = acos(ray->inter.x / (s->radius * sin(u)));
	u = ft_to_deg(u / (2 * M_PI));
	v = ft_to_deg((M_PI - v) / M_PI);
	if ((((int)(u / 10) % 2) && ((int)(v / 10) % 2)) || (!((int)(u / 10) % 2) && !((int)(v / 10) % 2)))
		s->color = (SDL_Color){0,0,0,255};
	else
		s->color = (SDL_Color){255,255,255,255};
	return (t);
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
