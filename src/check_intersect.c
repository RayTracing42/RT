/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/14 13:44:28 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	check_limit(t_ray *ray, t_list_objs *l, t_object *obj)
{
	double		dist;
	double		tmp;
	t_ray		tmp_ray;
	t_ray		res_ray;

	dist = 0;
	res_ray = *ray;
	while (l != NULL)
	{
		tmp_ray = first_intersect(ray, l->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			if (obj->is_in_obj(&tmp_ray.inter, obj))
			{
				dist = tmp;
				res_ray = tmp_ray;
			}
		}
		l = l->next;
	}
	*ray = res_ray;
	return (dist);
}

double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		dist;
	double		tmp;
	t_ray		tmp_ray;
	t_ray		res_ray;

	dist = 0;
	res_ray = *ray;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			if (limit_loop(&tmp_ray.inter, l_objs->obj->local_limit, l_objs->obj))
			{
				transform_inter(&tmp_ray, l_objs->obj);
				dist = tmp;
				res_ray = tmp_ray;
			}
			else
			{
				tmp = check_limit(&tmp_ray, l_objs->obj->local_limit, l_objs->obj);
				if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
				{
					transform_inter(&tmp_ray, tmp_ray.obj);
					dist = tmp;
					res_ray = tmp_ray;
				}
			}
			
		}
		l_objs = l_objs->next;
	}
	*ray = res_ray;
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
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}
