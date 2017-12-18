/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_limit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 09:59:45 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/18 12:16:17 by fcecilie         ###   ########.fr       */
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
	t_plane		tmp;

	l = father->limit;
	while (l)
	{
		p = (t_plane *)l->obj;
		if (p->lim_type == LOCAL)
		{
			if (tmp_ray->obj != l->obj)
			{
				tmp = *p;
	//			mult_vect(&tmp.normal, tmp.trans_inorm, &tmp.normal);
	//			mult_vect(&tmp.norm_diff, tmp.trans_const, &tmp.norm_diff);
				if (!(is_in_local_limit(&tmp_ray->inter, &tmp)))
					return (0);
			}
		}
		l = l->next;
	}
	return (1);
}
