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
			if (is_in_limit(&res_ray, &tmp_ray, l_objs->obj))
				dist = tmp;
			else
			{
			/*
				tmp_ray = second_intersect(ray, l_objs->obj, &tmp);
				if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
					if (is_in_limit(ray, &tmp_ray, l_objs->obj))
						dist = tmp;
			*/
			/**/
				tmp = dist;
				tmp_ray = intersect_full_obj(ray, l_objs->obj, &tmp);
				if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
				{
					dist = tmp;
					res_ray = tmp_ray;
				}
			/**/
			}
		}
		l_objs = l_objs->next;
	}
	*ray = res_ray;
	return (dist);
}

t_ray	intersect_full_obj(t_ray *ray, t_object *obj, double *dist)
{
	int		n;
	double	tmp;
	t_limit *l;
	t_ray	tmp_ray;
	t_ray	res_ray;

	l = &obj->local_limit;
	n = 0;
	res_ray = *ray;
	while (n < 6)
	{
		if (l->p[n])
		{
			tmp_ray = annex_intersect(ray, obj, (t_object *)l->p[n], &tmp);
			//tmp_ray = first_intersect(ray, (t_object *)l->p[n], &tmp);
			if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
			{
				if (obj->is_in_obj(&tmp_ray.inter, obj))
				{
				//	printf("(%.1f, %.1f, %.1f)\n", tmp_ray.inter.x, tmp_ray.inter.y, tmp_ray.inter.z);
					transform_inter(&tmp_ray, (t_object *)obj);
					res_ray = tmp_ray;
					*dist = tmp;
				}
			}
		}
		n++;
	}
	return (res_ray);
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

t_ray	annex_intersect(t_ray *ray, t_object *obj, t_object *lim, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	*tmp = lim->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), lim, 1);
	tmp_ray.normal = *lim->get_normal(&tmp_ray.inter, lim);
	tmp_ray.color = lim->color;
	tmp_ray.percuted_refractive_i = lim->obj_light.refractive_index;
	tmp_ray.obj = lim;
	return (tmp_ray);
}

