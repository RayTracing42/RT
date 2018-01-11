/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/11 06:37:03 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"


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

