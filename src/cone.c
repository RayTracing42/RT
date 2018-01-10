/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:05:50 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/10 18:46:22 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cone_intersection(t_ray *ray, t_parequation e,
	t_object *obj, int i)
{
	t_cone			*c;
	double			t;
	double			fac[3];

	c = (t_cone*)obj;
	t = -1;
	fac[_A] = e.vd.x * e.vd.x + e.vd.z * e.vd.z - e.vd.y * e.vd.y * c->tanalpha2;
	fac[_B] = 2 * (e.vd.x * e.vc.x + e.vd.z * e.vc.z - e.vd.y *
		e.vc.y * c->tanalpha2);
	fac[_C] = e.vc.x * e.vc.x + e.vc.z * e.vc.z - e.vc.y * e.vc.y * c->tanalpha2;
	if ((ray->nb_intersect = get_quad_equation_sol(&t, fac, i)))
		ray->inter = equation_get_dot(&e, t);
	return (t);
}

static const t_vector	*get_cone_normal(t_dot *inter, t_object *obj)
{
	t_cone	*c;

	c = (t_cone*)obj;
	c->normal = (t_vector){2 * inter->x, -2 * c->tanalpha2 * inter->y,
							2 * inter->z};
	return (&c->normal);
}

static int				is_in_cone(t_dot *i, t_object *obj)
{
	t_cone	*c;

	c = (t_cone*)obj;
	return ((pow(i->x, 2) + pow(i->z, 2) <= pow(i->y, 2) * c->tanalpha2));
}

t_cone					*new_cone(t_objs_comp args, double angle)
{
	t_cone	*c;

	c = (t_cone*)new_object(CONE, args);
	c->angle = angle;
	c->get_normal = get_cone_normal;
	c->is_in_obj = is_in_cone;
	c->intersect = cone_intersection;
	c->tanalpha2 = pow(tan(ft_to_rad(angle)), 2);
	return (c);
}

void					delete_cone(t_cone *cone)
{
	delete_object((t_object*)cone);
}
