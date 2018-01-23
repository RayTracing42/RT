/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/23 05:35:48 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	check_negative_intersect(t_ray *ray, t_list_objs *objs, const double t, double t2)
{
	t_ray		tmp_ray;
	t_list_objs	*list;
	double		tmp;
	double		tmp_dist;

	list = objs;
	while (list)
	{
		tmp_ray = first_intersect(ray, list->obj, &tmp);
		transform_inter(&tmp_ray, list->obj);
		limit(&tmp_ray, tmp_ray, tmp, &tmp_dist, NULL);
		if (tmp_ray.nb_intersect && lt(tmp_dist, t))
		{
			tmp_ray = second_intersect(ray, list->obj, &tmp);
			transform_inter(&tmp_ray, list->obj);
			limit(&tmp_ray, tmp_ray, tmp, &tmp, &tmp);
			if (gt(tmp, 0) && gt(tmp, t) && lt(tmp, t2))
			{
				if (list->obj->status == EMPTY)
					return (t2);
				*ray = tmp_ray;
				return (check_negative_intersect(ray, objs, tmp, t2));
			}
			else if (gt(tmp, 0) && gt(tmp, t))
				return (0);
		}
		list = list->next;
	}
	return (t);
}
