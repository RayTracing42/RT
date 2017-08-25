/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 11:04:54 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static int				in_boundary(t_ray *ray, t_cylinder *c, double t)
{
	t_dot		dot;

	if (c->height < 0)
		return (1);
	equation_get_dot(&dot, &ray->eq_obj, t);
	return (dot.y >= 0 && dot.y <= c->height);
}

static double			cylinder_intersect(t_ray *ray, t_cylinder *c)
{
	t_dot		res;
	t_vector	*vd;
	t_vector	*vc;
	double		t;

	t = -1;
	vc = &ray->eq_obj.vconst;
	vd = &ray->eq_obj.vdir;
	if (get_quad_equation_sol(&res, pow(vd->x, 2) + pow(vd->z, 2),
							2 * (vd->x * vc->x + vd->z * vc->z),
							pow(vc->x, 2) + pow(vc->z, 2) - c->r2))
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

static const t_vector	*get_cylinder_normal(t_dot *d, t_cylinder *c)
{
	(void)c;
	set_vector(&c->normal, 2 * d->x, 0, 2 * d->z);
	return (&c->normal);
}

t_cylinder				*new_cylinder(t_dot pos, double radius, double height)
{
	t_cylinder	*c;

	c = (t_cylinder*)new_object(CYLINDER, &cylinder_intersect,
								&get_cylinder_normal, sizeof(t_cylinder));
	translation(&c->trans, pos.x, pos.y, pos.z);
	translation(&c->trans_inv, -pos.x, -pos.y, -pos.z);
	c->radius = radius;
	c->r2 = pow(radius, 2);
	c->center = pos;
	c->height = height;
	return (c);
}
