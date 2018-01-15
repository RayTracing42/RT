/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hyperboloid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 16:57:05 by shiro             #+#    #+#             */
/*   Updated: 2018/01/15 08:35:48 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


static double			hyperboloid_intersection(t_ray *ray, t_parequation e,
	t_object *obj, int i)
{
	t_hyperboloid	*h;
	double			t;
	double			fac[3];

	h = (t_hyperboloid*)obj;
	fac[_A] = (e.vd.x * e.vd.x) / h->a2 - (e.vd.y * e.vd.y) / h->b2 + (e.vd.z * e.vd.z) / h->c2;
	fac[_B] = 2 * ((e.vd.x * e.vc.x) / h->a2 - (e.vd.y * e.vc.y) / h->b2 + (e.vd.z * e.vc.z) / h->c2);
	fac[_C] = (e.vc.x * e.vc.x) / h->a2 - (e.vc.y * e.vc.y) / h->b2 + (e.vc.z * e.vc.z) / h->c2 + h->d;
	if ((ray->nb_intersect = get_quad_equation_sol(&t, fac, i)))
	{
		ray->inter = equation_get_dot(&e, t);
		ray->obj = obj;
	}
	return (t);
}

static const t_vector	*get_hyperboloid_normal(t_dot *inter, t_object *obj)
{
	t_hyperboloid	*h;

	h = (t_hyperboloid*)obj;
	h->normal = (t_vector){(2 * inter->x) / h->a2, -(2 * inter->y) / h->b2, (2 * inter->z) / h->c2};
	return (&h->normal);
}

static int				is_in_hyperboloid(t_dot *i, t_object *obj)
{
	t_hyperboloid	*h;

	h = (t_hyperboloid*)obj;
	return (!((i->x * i->x) / h->a2 - (i->y * i->y) / h->b2 + (i->z * i->z) / h->c2 - 1));
}

t_hyperboloid			*new_hyperboloid(t_objs_comp args, double a, double b, double c, double d)
{
	t_hyperboloid	*h;

	h = (t_hyperboloid*)new_object(HYPERBOLOID, args);
	h->a2 = a * a;
	h->b2 = b * b;
	h->c2 = c * c;
	h->d = d;
	h->intersect = &hyperboloid_intersection;
	h->get_normal = &get_hyperboloid_normal;
	h->is_in_obj = &is_in_hyperboloid;
	return (h);
}

void					delete_hyperboloid(t_hyperboloid *h)
{
	delete_object((t_object*)h);
}
