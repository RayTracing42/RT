/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
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
	if ((lim->nb[0] && inter->x > *lim->nb[0])
		|| (lim->nb[1] && inter->y > *lim->nb[1])
		|| (lim->nb[2] && inter->z > *lim->nb[2])
		|| (lim->nb[3] && inter->x < *lim->nb[3])
		|| (lim->nb[4] && inter->y < *lim->nb[4])
		|| (lim->nb[5] && inter->z < *lim->nb[5]))
		return (0);
	return (1);
}

int		is_in_limit(t_ray *ray, t_ray *tmp_ray, t_object *obj)
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
