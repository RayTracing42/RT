/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 18:05:50 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 11:04:59 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static int				in_boundary(t_ray *ray, t_cone *c, double t)
{
	t_dot		dot;

	if (c->height < 0)
		return (1);
	equation_get_dot(&dot, &ray->eq_obj, t);
	return (dot.y >= 0 && dot.y <= c->height);
}

static double			cone_intersection(t_ray *ray, t_cone *c)
{
	t_dot		res;
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
	return (t);
}

static const t_vector	*get_cone_normal(t_dot *d, t_cone *c)
{
	set_vector(&c->normal, 2 * d->x, -2 * c->tanalpha2 * d->y, 2 * d->z);
	return (&c->normal);
}

t_cone					*new_cone(t_dot pos, double angle, double radius,
								double height)
{
	t_cone	*c;

	c = (t_cone*)new_object(CONE, cone_intersection, get_cone_normal,
							sizeof(t_cone));
	translation(&c->trans, pos.x, pos.y, pos.z);
	translation(&c->trans_inv, -pos.x, -pos.y, -pos.z);
	if (angle > 360)
		angle = angle - 360;
	if (angle < -360)
		angle = angle + 360;
	if (angle == 90)
		angle = 89;
	if (angle == -90)
		angle = -89;
	c->angle = angle;
	c->center = pos;
	c->height = height;
	c->radius = radius;
	c->tanalpha2 = pow(tan(ft_to_rad(angle)), 2);
	if (height <= 0 && radius > 0 && c->tanalpha2)
		c->height = radius / tan(ft_to_rad(angle));
	return (c);
}
