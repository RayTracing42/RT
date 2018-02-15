/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/15 15:38:28 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_obj(const double t, const t_dot inter, t_object *obj)
{
	double	tmp;
	t_ray	ray;

	ray.equ = (t_parequation){*(t_vector*)&inter, (t_vector){0.01, 0.0001, 0.01}};
	first_intersect(&ray, obj, &tmp);
	if (le(tmp, t))
	{
		second_intersect(&ray, obj, &tmp);
		if (le(t, tmp))
			return (1);
	}
	return (0);
}

int		is_in_limited_obj(const double *t, const t_ray *ray, t_object *obj)
{
	double	t_tmp;
	t_ray	tmp;

	tmp.equ = (t_parequation){*(t_vector*)&ray->inter, (t_vector){0, 0, 0.01}};
	first_intersect(&tmp, obj, &t_tmp);
	if (le(t_tmp, *t))
	{
		second_intersect(&tmp, obj, &t_tmp);
		if (le(*t, t_tmp))
		{
			if (obj->limit)
			{
				if (is_in_limit(ray, obj))
					return (1);
			}
			else
				return (1);
		}
	}
	return (0);
}
