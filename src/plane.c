/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 12:35:04 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 13:31:10 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			plane_intersect(t_ray *ray, t_plane *p)
{
	(void)p;
	(void)ray;
	return (0);
	/*double		t;
	double		denom;
	t_vector	*vd;
	t_vector	*vc;

	vd = &ray->eq_obj.vdir;
	vc = &ray->eq_obj.vconst;
	denom = (p->a * vd->x + p->b * vd->y + p->c * vd->z);
	if (!denom)
		return (-1);
	t = -((p->a * vc->x + p->b * vc->y + p->c * vc->z + p->d) / denom);
	if ((long)(t * pow(10, 12)) > 0)
		return (t);
	return (-1);*/
}

static const t_vector	*get_plane_normal(t_dot *d, t_plane *p)
{
	(void)d;
	return (&p->normal);
}

/*int						is_in_plane(t_dot *d, t_plane *p)
{
}*/

t_plane					*new_plane(t_objs_comp args, t_vector normal)
{
	t_plane		*plane;

	plane = (t_plane*)new_object(PLANE, args.orig, args.dir, args.col);
	plane->normal = normal;
	plane->get_normal = get_plane_normal;
	plane->intersect = plane_intersect;
	return (plane);
}
