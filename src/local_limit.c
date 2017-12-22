/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_limit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 09:59:45 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/22 09:13:32 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_local_limit(t_dot *i, t_plane *p)
{
	double  distance_1;
	double  distance_2;

	distance_1 = get_dot_dist(i,
		&(t_dot){(p->norm_diff.x + p->normal.x),
		(p->norm_diff.y + p->normal.y),
		(p->norm_diff.z + p->normal.z)});
	distance_2 = get_dot_dist(i,
		&(t_dot){(p->norm_diff.x - p->normal.x),
		(p->norm_diff.y - p->normal.y),
		(p->norm_diff.z - p->normal.z)});
	return ((distance_1 >= distance_2));
}

int		local_limit_loop(t_ray *tmp_ray, t_object *father)
{
	t_list_objs	*l;
	t_plane		*p;

	l = father->limit;
	while (l)
	{
		p = (t_plane *)l->obj;
		if (p->lim_type == LOCAL)
		{
			if (tmp_ray->obj != l->obj)
			{
				if (!(is_in_local_limit(&tmp_ray->inter, p)))
					return (0);
			}
		}
		l = l->next;
	}
	return (1);
}

int		transformed_local_limit_loop(t_ray *tmp_ray, t_object *father)
{
	t_list_objs	*l;
	t_plane		*p;
	t_plane		r;
	t_ray		trans_ray;
	t_vector	center;

	l = father->limit;
	while (l)
	{
		p = (t_plane *)l->obj;
		if (p->lim_type == LOCAL)
		{
			if (tmp_ray->obj != l->obj)
			{
				r = *p;
				trans_ray = *tmp_ray;
				center = (t_vector){father->origin.x, father->origin.y, father->origin.z};
				mult_vect(&r.normal, p->trans_norm, &r.normal);
				mult_vect(&r.norm_diff, father->trans_const, &r.norm_diff);
				r.norm_diff.x += center.x;
				r.norm_diff.y += center.y;
				r.norm_diff.z += center.z;
				if (!(is_in_local_limit(&trans_ray.inter, &r)))
					return (0);
			}
		}
		l = l->next;
	}
	return (1);
}
