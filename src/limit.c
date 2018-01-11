/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:27:56 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/11 13:54:38 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_in_right_side_of_limit(const t_dot *i, t_object *p)
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

int		empty_limit(t_ray *ray, t_ray *tmp_ray, t_object *father)
{
	transform_inter(tmp_ray, tmp_ray->obj);
	if (is_in_limit(tmp_ray, father))
	{
		*ray = *tmp_ray;
		return (1);
	}
	return (0);
}

int		full_limit(t_ray *ray, t_ray *tmp_ray, t_object *father)
{
	t_vector	center;

	mult_vect(&center, father->trans_const, &(t_vector){0, 0, 0});
	center.x += father->origin.x;
	center.y += father->origin.y;
	center.z += father->origin.z;
	transform_inter(tmp_ray, tmp_ray->obj);
	if (is_in_limit(tmp_ray, father))
	{
		tmp_ray->inter.x -= center.x;
		tmp_ray->inter.y -= center.y;
		tmp_ray->inter.z -= center.z;
		if (father->is_in_obj(&tmp_ray->inter, father))
		{
			tmp_ray->inter.x += center.x;
			tmp_ray->inter.y += center.y;
			tmp_ray->inter.z += center.z;
			*ray = *tmp_ray;
			return (1);
		}
	}
	return (0);
}

void	check_limit_intersect(t_ray *ray, t_object *father, double *dist)
{
	double		tmp;
	t_ray		tmp_ray;
	t_list_objs	*l;
	t_plane		*p;

	l = father->limit;
	while (l)
	{
		p = (t_plane *)l->obj;
		tmp_ray = (p->status == 0) ? second_intersect(ray, father, &tmp) :
			first_intersect(ray, l->obj, &tmp);
		if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
		{
			if (p->status == 0)
				if (empty_limit(ray, &tmp_ray, father))
					*dist = tmp;
			if (p->status == 1)
				if (full_limit(ray, &tmp_ray, father))
					*dist = tmp;
		}
		l = l->next;
	}
}
