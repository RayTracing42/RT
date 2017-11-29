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

void	first_intersect(t_ray *ray, t_object *obj, double *dist)
{
	double	tmp;
	t_ray	tmp_ray;

	tmp_ray = *ray;
	tmp = obj->intersect_1(&tmp_ray.nb_intersect, &tmp_ray.inter,
			transform_equ(&tmp_ray, obj), obj);
	if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
	{
		*ray = tmp_ray;
		transform_inter(ray, obj);
		ray->color = obj->color;
		ray->obj = obj;
		ray->percuted_refractive_i = obj->obj_light.refractive_index;
		*dist = tmp;
	}
}

void	second_intersect(t_ray *ray, t_object *obj, double *dist)
{
	double	tmp;
	t_ray	tmp_ray;

	tmp_ray = *ray;
	tmp = obj->intersect_2(&tmp_ray.nb_intersect, &tmp_ray.inter,
			transform_equ(&tmp_ray, obj), obj);
	if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
	{
		*ray = tmp_ray;
		transform_inter(ray, obj);
		ray->color = obj->color;
		ray->obj = obj;
		ray->percuted_refractive_i = obj->obj_light.refractive_index;
		*dist = tmp;
	}
}
