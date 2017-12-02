/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limits.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:57:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/11/29 04:06:37 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		test_limit(t_dot *inter, t_limit *lim)
{
	if ((lim->up_x && inter->x > *lim->up_x)
		|| (lim->up_y && inter->y > *lim->up_y)
		|| (lim->up_z && inter->z > *lim->up_z)
		|| (lim->down_x && inter->x < *lim->down_x)
		|| (lim->down_y && inter->y < *lim->down_y)
		|| (lim->down_z && inter->z < *lim->down_z))
		return (0);
	return (1);
}

int		is_in_limits(t_ray *ray, t_ray *tmp_ray, t_object *obj)
{
	if (test_limit(&tmp_ray->inter, &obj->local_limit))
	{
		transform_inter(tmp_ray, obj);
		if (test_limit(&tmp_ray->inter, &obj->global_limit))
		{
			ray->inter = tmp_ray->inter;
			ray->normal = tmp_ray->normal;
			ray->nb_intersect = tmp_ray->nb_intersect;
			ray->color = obj->color;
			ray->obj = obj;
			ray->percuted_refractive_i = obj->obj_light.refractive_index;
			return (1);
		}
		else
			return (0);
	}
	else
		return (0);
}
