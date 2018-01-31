/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:27:56 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/31 05:47:00 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		is_in_right_side_of_limit(t_dot i, t_object *p)
{
	double	distance_1;
	double	distance_2;

	distance_1 = get_dot_dist(&i,
			&(t_dot){(p->origin.x + p->normal.x),
			(p->origin.y + p->normal.y),
			(p->origin.z + p->normal.z)});
	distance_2 = get_dot_dist(&i,
			&(t_dot){(p->origin.x - p->normal.x),
			(p->origin.y - p->normal.y),
			(p->origin.z - p->normal.z)});
	return ((distance_1 >= distance_2));
}

int				is_in_limit(const t_ray *ray, t_object *father)
{
	t_list_objs	*l;

	l = father->limit;
	while (l)
	{
		if (ray->obj != l->obj)
		{
			if (!is_in_right_side_of_limit(ray->inter, l->obj))
				return (0);
		}
		l = l->next;
	}
	return (1);
}

void	unvalid_point_in_limit(t_couple_ray *basic, t_object *father)
{
	if (father->limit)
	{
		if (basic->a.nb_intersect > 0
			&& !is_in_limit(&basic->a, father))
			basic->a.nb_intersect = 0;
		if (basic->b.nb_intersect > 0
			&& !is_in_limit(&basic->b, father))
			basic->b.nb_intersect = 0;
	}
}

t_couple_ray	limit(t_couple_ray *basic, t_object *father, const t_ray *ray)
{
	t_couple_ray	limited;
	t_list_objs		*l;
	t_ray			tmp;
	double			t_tmp;

	l = father->limit;
	limited.a.nb_intersect = 0;
	limited.b.nb_intersect = 0;
	while (l)
	{
		tmp = first_intersect(ray, l->obj, &t_tmp);
		if (tmp.nb_intersect > 0)
		{
			transform_inter(&tmp, l->obj);
			if (is_in_limit(&tmp, father))
				if (is_in_obj(t_tmp, tmp.inter, father))
					limit2(&limited, &tmp, &t_tmp);
		}
		l = l->next;
	}
//	unvalid_point_in_limit(basic, father);
	return (limited);
}
