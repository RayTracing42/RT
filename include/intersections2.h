/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections2.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/15 15:01:39 by shiro             #+#    #+#             */
/*   Updated: 2018/02/15 15:02:04 by shiro            ###   ########.fr       */
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
