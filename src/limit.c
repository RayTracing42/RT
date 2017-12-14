/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:57:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/14 13:44:31 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_limit(t_dot *i, t_plane *p)
{
	double	distance_1;
	double	distance_2;

	distance_1 = get_dot_dist(i,
		&(t_dot){(p->exceeding_limit.x + p->normal.x),
		(p->exceeding_limit.y + p->normal.y),
		(p->exceeding_limit.z + p->normal.z)});
	distance_2 = get_dot_dist(i,
		&(t_dot){(p->exceeding_limit.x - p->normal.x),
		(p->exceeding_limit.y - p->normal.y),
		(p->exceeding_limit.z - p->normal.z)});
	return ((distance_1 >= distance_2));
}

int		limit_loop(t_dot *i, t_list_objs *l, t_object *father)
{
	while (l)
	{
		if (father != l->obj)
		{
			if (!(is_in_limit(i, (t_plane *)l->obj)))
				return (0);
		}
		l = l->next;
	}
	return (1);
}
