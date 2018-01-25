/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/25 14:34:55 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		negative_obj(t_couple_ray *basic, t_object *father, const t_ray *ray)
{
	t_couple_ray	neg;
	t_couple_ray	tmp;
	t_list_objs		*l;

	l = father->negative_obj;
	neg = *basic;
	while (l)
	{
		tmp.a = first_intersect(ray, l->obj, &tmp.ta);
		tmp.b = second_intersect(ray, l->obj, &tmp.tb);
		if (!eq(tmp.ta, 0) && !eq(tmp.tb, 0))
		{
			transform_inter(&tmp.a, l->obj);
			transform_inter(&tmp.b, l->obj);
			if (l->obj->limit)
				limit(&tmp, l->obj, ray);
			if (tmp.ta < neg.ta && neg.ta < tmp.tb)
			{
				valid_ray(&neg.a, &neg.ta, &tmp.b, &tmp.tb);
				negative_obj(&neg, father, ray);
			}
			if (tmp.ta < neg.tb && neg.tb < tmp.tb)
			{
				valid_ray(&neg.b, &neg.tb, &tmp.a, &tmp.ta);
				negative_obj(&neg, father, ray);
			}
		}
		l = l->next;
	}
	return (non_inverted_intersect(basic, &neg, 0));
}
