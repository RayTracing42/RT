/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2017/11/29 04:06:35 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_ray	limit_intersect(t_ray *ray, t_object *obj, t_object *father, double *tmp)
{
	t_ray	tmp_ray;


	father = (t_object *)father;

	tmp_ray = *ray;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 1);
	tmp_ray.normal = *obj->get_normal(&tmp_ray.inter, obj);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}

double	check_limit(t_ray *ray, t_list_objs *l, t_object *obj)
{
	double		dist;
	double		tmp;
	t_ray		tmp_ray;
	t_ray		res_ray;

	t_plane		*p;
	obj = (t_object *)obj;

	dist = 0;
	res_ray = *ray;
	while (l != NULL)
	{
	//	tmp_ray = limit_intersect(ray, l->obj, obj, &tmp);
		tmp_ray = first_intersect(ray, l->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			p = (t_plane*)l->obj;
			tmp_ray.inter.x -= p->exceeding_limit.x;
			tmp_ray.inter.y -= p->exceeding_limit.y;
			tmp_ray.inter.z -= p->exceeding_limit.z;
			if (obj->is_in_obj(&tmp_ray.inter, obj))
			{
			transform_inter(&tmp_ray, tmp_ray.obj);
				
			//	printf("valid(%.2f, %.2f, %.2f)\n", tmp_ray.inter.x, tmp_ray.inter.y, tmp_ray.inter.z);
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