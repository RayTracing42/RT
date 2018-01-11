/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/11 04:10:39 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_obj(t_dot *inter, t_ray *ray, t_object *obj)
{
	t_ray	first;
	t_ray	second;
	double	a;
	double	b;
	double	c;
	double	tmp;

	first = first_intersect(ray, obj, &tmp);
	if (tmp)
	{
		transform_inter(&first, obj);
		c = get_dot_dist(inter, (t_dot*)&ray->equ.vc);
		a = get_dot_dist(&first.inter, (t_dot*)&ray->equ.vc);
		if (a < c)
		{
			second = second_intersect(ray, obj, &tmp);
			if (tmp)
			{
				transform_inter(&second, obj);
				b = get_dot_dist(&second.inter, (t_dot*)&ray->equ.vc);
				if (c < b)
					return (1);
			}
		}
	}
	return (0);
}

void	limit(t_ray *ray, t_ray *tmp_ray, double *tmp, double *dist)
{
	t_object *obj;

	obj = tmp_ray->obj;
	if (is_in_limit(tmp_ray, obj))
		*dist = *tmp;
	else
		*tmp_ray = check_limit_intersect(ray, obj, dist);
	*ray = *tmp_ray;
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
			transform_inter(&tmp_ray, tmp_ray.obj);
			limit(&res_ray, &tmp_ray, &tmp, &dist);
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
	tmp_ray.normal = (t_vector){-tmp_ray.normal.x, -tmp_ray.normal.y,
		-tmp_ray.normal.z};
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}
