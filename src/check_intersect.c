/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/17 13:48:46 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_limit(t_ray *ray, t_list_objs *l, t_object *obj, double *dist)
{
	double		tmp;
	t_ray		tmp_ray;
	t_plane		*p;

	while (l != NULL)
	{
		p = (t_plane *)l->obj;
		tmp_ray = (p->status == 0) ? second_intersect(ray, obj, &tmp) :
			first_intersect(ray, l->obj, &tmp);
		if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
		{
			if (p->status == 0)
				if (empty_limit(ray, &tmp_ray, obj))
					*dist = tmp;
			if (p->status == 1)
				if (full_limit(ray, &tmp_ray, obj))
					*dist = tmp;
		}
		l = l->next;
	}
}

double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		dist;
	double		tmp;
	t_ray		tmp_ray;

	dist = 0;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			if (limit_loop(&tmp_ray, l_objs->obj))
			{
				transform_inter(&tmp_ray, tmp_ray.obj);
				dist = tmp;
				*ray = tmp_ray;
			}
			else
				check_limit(ray, l_objs->obj->limit, l_objs->obj, &dist);
		}
		l_objs = l_objs->next;
	}
	return (dist);
}

t_ray	first_intersect(t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 1);
	tmp_ray.normal = *obj->get_normal(&tmp_ray.inter, obj);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}

t_ray	second_intersect(t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 2);
	tmp_ray.normal = *obj->get_normal(&tmp_ray.inter, obj);
//	tmp_ray.normal = (t_vector){-tmp_ray.normal.x, -tmp_ray.normal.y,
//		-tmp_ray.normal.z};
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}
