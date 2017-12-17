/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_limit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 09:59:45 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/17 13:27:17 by fcecilie         ###   ########.fr       */
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
