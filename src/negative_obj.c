/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/04 06:11:48 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_negative_obj(t_ray *ray, t_object *father)
{
	t_list_objs		*n;
	t_dot			test;
	t_vector		center = {0, 0, 0};
	t_matrix		*tmp;
	
	n = father->negative_obj;
	while (n)
	{
		if (ray->obj != n->obj)
		{
			mult_vect(&center, n->obj->trans_const, &(t_vector){0, 0, 0});
			center.x += n->obj->origin.x;
			center.y += n->obj->origin.y;
			center.z += n->obj->origin.z;
			test = ray->inter;
//			tmp = father->trans_const;
//			mult_vect((t_vector*)&test, neg_matrix(&tmp, father->trans_const), (t_vector*)&test);
			tmp = n->obj->trans_const;
			mult_vect((t_vector*)&test, neg_matrix(&tmp, n->obj->trans_const), (t_vector*)&test);
			test.x -= center.x;
			test.y -= center.y;
			test.z -= center.z;
//			printf("(%f, %f, %f) \n", test.x, test.y, test.z);
			if (n->obj->is_in_obj(&test, n->obj))
				return (1);
		}
		n = n->next;
	}
	return (0);
}
