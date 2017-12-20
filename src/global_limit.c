/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_limit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 10:10:57 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/20 07:48:51 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_global_limit(t_dot *i, t_plane *p)
{
	double	distance_1;
	double	distance_2;

	distance_1 = get_dot_dist(i,
		&(t_dot){(p->origin.x + p->normal.x),
		(p->origin.y + p->normal.y),
		(p->origin.z + p->normal.z)});
	distance_2 = get_dot_dist(i,
		&(t_dot){(p->origin.x - p->normal.x),
		(p->origin.y - p->normal.y),
		(p->origin.z - p->normal.z)});
	return ((distance_1 >= distance_2));
}

int		global_limit_loop(t_ray *tmp_ray, t_object *father)
{
	t_list_objs *l;
	t_plane		*p;
	t_ray		trans_ray;

	l = father->limit;
	while (l)
	{
		p = (t_plane *)l->obj;
		if (tmp_ray->obj != l->obj)
		{
			if (p->lim_type == GLOBAL)
			{
				trans_ray = *tmp_ray;
				transform_inter(&trans_ray, trans_ray.obj);
				if (!(is_in_global_limit(&trans_ray.inter, p)))
					return (0);
			}
		}
		l = l->next;
	}
	return (1);
}
