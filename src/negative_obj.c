/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/09 06:07:12 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	is_in_negative_obj(t_ray *ray, t_object *father)
{
	t_list_objs	*n;
	t_ray		first_ray;
	t_ray		secnd_ray;
	double		first_tmp;
	double		secnd_tmp;
	double		inter_tmp;
	double		tmp;

	n = father->negative_obj;
	while (n)
	{
		first_ray = first_intersect(ray, n->obj, &first_tmp);
		secnd_ray = second_intersect(ray, n->obj, &secnd_tmp);
		tmp = secnd_tmp;
		transform_inter(&first_ray, first_ray.obj);
		transform_inter(&secnd_ray, secnd_ray.obj);
		first_tmp = get_dot_dist((t_dot*)&ray->equ.vc, &first_ray.inter);
		secnd_tmp = get_dot_dist((t_dot*)&ray->equ.vc, &secnd_ray.inter);
		inter_tmp = get_dot_dist((t_dot*)&ray->equ.vc, &ray->inter);
		if (first_tmp < inter_tmp && inter_tmp < secnd_tmp)
		{
			*ray = secnd_ray;
			return (tmp);
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
