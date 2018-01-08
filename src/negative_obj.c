/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/08 06:09:52 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	C'est foireux;
*/

int		is_in_negative_obj(t_ray *ray, t_object *father)
{
	t_list_objs		*n;
	t_dot			reverse_inter;
//	t_vector		center = {0, 0, 0};

	n = father->negative_obj;
	while (n)
	{
		if (ray->obj != n->obj)
		{
	// 1) soustraire l'origine de l'obj negatif au point d'inter;
	// 2) appliquer au point d'inter la translation inverse de l'obj negatif;
	// 3) appliquer au point d'inter la rotation inverse de l'obj negatif;
	// 4) verifier si le point d'inter se trouve dans l'obj;

			/*mult_vect(&center, father->trans_const, &(t_vector){0, 0, 0});
			center.x += father->origin.x;
			center.y += father->origin.y;
			center.z += father->origin.z;
			reverse_inter = ray->inter;
			reverse_inter.x -= center.x;
			reverse_inter.y -= center.y;
			reverse_inter.z -= center.z;
			mult_vect((t_vector*)&reverse_inter, n->obj->trans_iconst,
					(t_vector*)&reverse_inter);*/
			if (n->obj->is_in_obj(&reverse_inter, n->obj))
				return (1);
		}
		n = n->next;
	}
	return (0);
}

void	check_negative_obj_intersect(t_ray *ray, t_object *father, double *dist)
{
	ray = (t_ray*)ray;
	father = (t_object*)father;
	dist = (double *)dist;
	*ray = second_intersect(ray, father, dist);
}
