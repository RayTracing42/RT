/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_limit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 09:59:45 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/17 10:10:49 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_local_limit(t_dot *i, t_plane *p)
{
	double  distance_1;
	double  distance_2;

	distance_1 = get_dot_dist(i,
		&(t_dot){(p->orig_diff.x + p->normal.x),
		(p->orig_diff.y + p->normal.y),
		(p->orig_diff.z + p->normal.z)});
	distance_2 = get_dot_dist(i,
		&(t_dot){(p->orig_diff.x - p->normal.x),
		(p->orig_diff.y - p->normal.y),
		(p->orig_diff.z - p->normal.z)});
	return ((distance_1 >= distance_2));
}

int		local_limit_loop(t_ray *tmp_ray, t_object *father)
{
	t_list_objs		*l;

	l = father->local_limit;
	while (l)
	{
		if (l->obj != tmp_ray->obj)
		{
			if (!(is_in_local_limit(&tmp_ray->inter, (t_plane *)l->obj)))
				return (0);
		}
		l = l->next;
	}
	return (1);
}
