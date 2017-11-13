/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:05:50 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/12 20:05:29 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cone_intersection(int *nbi, t_dot *dst, t_parequation e, t_object *obj)
{
	t_cone		*c;
	double		t;

	t = -1;
	c = (t_cone*)obj;
	if ((*nbi = get_quad_equation_sol(&t,
			pow(e.vd.x, 2) + pow(e.vd.z, 2) - pow(e.vd.y, 2) * c->tanalpha2,
			2 * (e.vd.x * e.vc.x + e.vd.z * e.vc.z - e.vd.y * e.vc.y * c->tanalpha2),
			pow(e.vc.x, 2) + pow(e.vc.z, 2) - pow(e.vc.y, 2) * c->tanalpha2)))
		*dst = equation_get_dot(&e, t);
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

t_cone					*new_cone(t_objs_comp args, double angle,
								double height_top, double height_bottom)
{
	t_cone	*c;

	c = (t_cone*)new_object(CONE, args);
	c->angle = angle;
	c->height_top = height_top;
	c->height_bottom = height_bottom;
	c->get_normal = get_cone_normal;
	c->intersect = cone_intersection;
	c->tanalpha2 = pow(tan(ft_to_rad(angle)), 2);
	return (c);
}

void					delete_cone(t_cone *cone)
{
	delete_object((t_object*)cone);
}
