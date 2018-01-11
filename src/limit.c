/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:27:56 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/11 04:02:48 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_right_side_of_limit(t_dot *i, t_object *p)
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

int		is_in_limit(t_ray *ray, t_object *father)
{
	t_list_objs	*l;

	l = father->limit;
	while (l)
	{
		if (ray->obj != l->obj)
		{
			if (!is_in_right_side_of_limit(&ray->inter, l->obj))
				return (0);
		}
		l = l->next;
	}
	return (1);
}

int		empty_limit(t_ray *tmp_ray, t_object *father)
{
	if (is_in_limit(tmp_ray, father))
		return (1);
	return (0);
}

int		full_limit(t_ray *tmp_ray, t_object *father)
{

	if (is_in_limit(tmp_ray, father))
	{
		if (is_in_obj(&tmp_ray->inter, tmp_ray, father))
			return (1);
	}
	return (0);
}

t_ray	check_limit_intersect(t_ray *ray, t_object *father, double *dist)
{
	double		tmp;
	t_ray		tmp_ray;
	t_ray		res_ray;
	t_list_objs	*l;
	t_plane		*p;

	l = father->limit;
	res_ray = *ray;
	while (l)
	{
		p = (t_plane *)l->obj;
		tmp_ray = (p->status == 0) ? second_intersect(ray, father, &tmp) :
			first_intersect(ray, l->obj, &tmp);
		if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
		{
			transform_inter(&tmp_ray, tmp_ray.obj);
			if ((p->status == 0 && empty_limit(&tmp_ray, father))
				|| (p->status == 1 && full_limit(&tmp_ray, father)))
			{
				res_ray = tmp_ray;
				*dist = tmp;
			}
		}
		l = l->next;
	}
	return (res_ray);
}
