/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:05:50 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 15:08:27 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			cone_intersection(t_ray *ray, t_cone *c)
{
	(void)c;
	(void)ray;
	return (0);
	/*t_dot		res;
	t_vector	*vd;
	t_vector	*vc;
	double		t;

	t = -1;
	vc = &ray->eq_obj.vconst;
	vd = &ray->eq_obj.vdir;
	if (get_quad_equation_sol(&res,
			pow(vd->x, 2) + pow(vd->z, 2) - pow(vd->y, 2) * c->tanalpha2,
			2 * (vd->x * vc->x + vd->z * vc->z - vd->y * vc->y * c->tanalpha2),
			pow(vc->x, 2) + pow(vc->z, 2) - pow(vc->y, 2) * c->tanalpha2))
	{
		if ((long)(res.x * pow(10, 12)) > 0 && in_boundary(ray, c, res.x))
		{
			if ((long)(res.y * pow(10, 12)) > 0 && in_boundary(ray, c, res.y))
				t = (res.x < res.y ? res.x : res.y);
			else
				t = (res.x);
		}
		else if ((long)(res.y * pow(10, 12)) > 0 && in_boundary(ray, c, res.y))
			t = (res.y);
	}
	return (t);*/
}

static const t_vector	*get_cone_normal(t_dot *d, t_cone *c)
{
	(void)d;
	//set_vector(&c->normal, 2 * d->x, -2 * c->tanalpha2 * d->y, 2 * d->z);
	return (&c->normal);
}

t_cone					*new_cone(t_objs_comp args, double angle,
								double height_top, double height_bottom)
{
	t_cone	*c;

	c = (t_cone*)new_object(CONE, args.orig, args.dir, args.col);
	c->angle = angle;
	c->height_top = height_top;
	c->height_bottom = height_bottom;
	c->get_normal = get_cone_normal;
	c->intersect = cone_intersection;
//	c->tanalpha2 = pow(tan(ft_to_rad(angle)), 2);
	return (c);
}

void					delete_cone(t_cone *cone)
{
	delete_object((t_object*)cone);
}
