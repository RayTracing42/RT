/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:57:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/16 10:39:32 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_limit(t_dot *i, t_plane *p)
{
	double	distance_1;
	double	distance_2;

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

void	normalized_diff(t_plane *p, t_dot *trans)
{
	double		dist;
	double		angle;
	t_vector	n;
	t_vector	o;

	o = (t_vector){p->orig_diff.x, p->orig_diff.y, p->orig_diff.z};
	if (!(o.x == 0 && o.y == 0 && o.z == 0))
	{
		n = p->normal;
		vect_normalize(&n);
		vect_normalize(&o);
		angle = angle_between_vectors(n, o);
		dist = get_vect_lenght(&p->orig_diff) * cos(angle * M_PI / 180);
		p->norm_diff = (t_vector){n.x * dist, n.y * dist, n.z * dist};
	}
	else
		p->norm_diff = (t_vector){0, 0, 0};
	trans->x += p->norm_diff.x;
	trans->y += p->norm_diff.y;
	trans->z += p->norm_diff.z;
}
