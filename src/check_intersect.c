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
	tmp_ray.equ = transform_equ(&tmp_ray, obj);
	tmp = obj->intersect(&tmp_ray, obj, 1);
	if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
	{
		if (test_limit(&tmp_ray.inter, &obj->local_limit))
		{
			transform_inter(&tmp_ray, obj);
			if (test_limit(&tmp_ray.inter, &obj->global_limit))
			{
				ray->inter = tmp_ray.inter;
				ray->normal = tmp_ray.normal;
				ray->color = obj->color;
				ray->obj = obj;
				ray->percuted_refractive_i = obj->obj_light.refractive_index;
				ray->nb_intersect = tmp_ray.nb_intersect;
				*dist = tmp;
			}
		}
	}
}

void	second_intersect(t_ray *ray, t_object *obj, double *dist)
{
	double	tmp;
	t_ray	tmp_ray;

	tmp_ray = *ray;
	tmp_ray.equ = transform_equ(&tmp_ray, obj);
	tmp = obj->intersect(&tmp_ray, obj, 2);
	if (gt(tmp, 0) && (eq(*dist, 0) || (lt(tmp, *dist) && gt(*dist, 0))))
	{
		ray->inter = tmp_ray.inter;
		ray->nb_intersect = tmp_ray.nb_intersect;
		transform_inter(ray, obj);
		ray->color = obj->color;
		ray->obj = obj;
		ray->percuted_refractive_i = obj->obj_light.refractive_index;
		*dist = tmp;
	}
}
