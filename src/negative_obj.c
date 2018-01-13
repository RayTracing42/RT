/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/13 13:52:04 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	check_negative_intersect(t_ray *ray, t_list_objs *objs, const double t, double t2)
{
	t_ray		tmp_ray;
	t_list_objs	*list;
	double		tmp;

	list = objs;
	while (list)
	{
		tmp_ray = first_intersect(ray, list->obj, &tmp);
		transform_inter(&tmp_ray, list->obj);
		limit(&tmp_ray, tmp_ray, tmp, &tmp, 1);
		if ((gt(tmp, 0) || lt(t2, 0)) && lt(tmp, t))
		{
			tmp_ray = second_intersect(ray, list->obj, &tmp);
			transform_inter(&tmp_ray, list->obj);
			limit(&tmp_ray, tmp_ray, tmp, &tmp, 1);
			if (gt(tmp, 0) && gt(tmp, t) && lt(tmp, t2) && gt(t2, 0))
			{
				if (list->obj->status == EMPTY)
					return (t2);
				*ray = tmp_ray;
				return(check_negative_intersect(ray, objs, tmp, t2));
			}
			else if ((gt(tmp, 0) && gt(tmp, t)) || lt(t2, 0))
				return (0);
		}
		list = list->next;
	}
	return (t);
}

void	check_negative_obj_intersect(t_ray *ray, t_object *father, double *dist)
{
	t_list_objs	*n;
	t_ray		secnd_neg;
	double		tmp;
	int			reset;
	int			res;

	n = father->negative_obj;
	while (n)
	{
		if (is_in_obj(&ray->inter, ray, n->obj))
		{
			secnd_neg = second_intersect(ray, n->obj, &tmp);
			transform_inter(&secnd_neg, n->obj);
			if ((res = is_in_obj(&secnd_neg.inter, &secnd_neg, father)))
			{
				*dist = tmp;
				*ray = secnd_neg;
				reset = 1;
			}
			if (res == 0)
			{
				*dist = 0;
				return ;
			}
		}
		n = n->next;
		if (reset)
		{
			reset = 0;
			n = father->negative_obj;
		}
	}
}
