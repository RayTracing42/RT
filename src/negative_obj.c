/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/05 03:13:17 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	On ramene inter aux positions 0 puis on lui fait subir la transfo inverse
**		de l'objet negatif;
*/

int		is_in_negative_obj(t_ray *ray, t_object *father)
{
	t_list_objs		*n;
	t_dot			reverse_inter;
	t_vector		center = {0, 0, 0};

	n = father->negative_obj;
	while (n)
	{
		if (ray->obj != n->obj)
		{
			mult_vect(&center, father->trans_const, &(t_vector){0, 0, 0});
			center.x += father->origin.x;
			center.y += father->origin.y;
			center.z += father->origin.z;
			reverse_inter = ray->inter;
			reverse_inter.x -= center.x;
			reverse_inter.y -= center.y;
			reverse_inter.z -= center.z;
			mult_vect((t_vector*)&reverse_inter, n->obj->trans_iconst,
					(t_vector*)&reverse_inter);
			if (n->obj->is_in_obj(&reverse_inter, n->obj))
				return (1);
		}
		n = n->next;
	}
	return (0);
}

void	check_negative_obj_intersect(t_ray *ray, t_object *father, double *dist)
{
//	double		tmp;
//	t_ray		tmp_ray;
	t_list_objs	*n;

	n = father->negative_obj;
	while (n)
	{
//merdier;
		*dist = (double)*dist;
		ray = (t_ray *)ray;
		n = n->next;
	}

}