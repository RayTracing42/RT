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

	dist = 0;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			if (is_in_limits(ray, &tmp_ray, l_objs->obj))
				dist = tmp;
			else
			{
				tmp_ray = second_intersect(ray, l_objs->obj, &tmp);
				if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
					if (is_in_limits(ray, &tmp_ray, l_objs->obj))
						dist = tmp;
			}
		}
		l_objs = l_objs->next;
	}
	return (dist);
}

t_ray	first_intersect(t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	tmp_ray.equ = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, obj, 1);
	return (tmp_ray);
}

t_ray	second_intersect(t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	tmp_ray.equ = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, obj, 2);
	return (tmp_ray);
}
