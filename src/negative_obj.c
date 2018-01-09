/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/09 04:11:37 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		transformed_is_in_obj(t_ray *ray, t_object *father)
{
	t_vector	center;
	t_ray		tmp_ray;

	tmp_ray = *ray;
	mult_vect(&center, father->trans_const, &(t_vector){0, 0, 0});
	center.x += father->origin.x;
	center.y += father->origin.y;
	center.z += father->origin.z;
	if (is_in_limit(&tmp_ray, father))
	{
		tmp_ray.inter.x -= center.x;
		tmp_ray.inter.y -= center.y;
		tmp_ray.inter.z -= center.z;
		if (father->is_in_obj(&tmp_ray.inter, father))
			return (1);
	}
	return (0);

}

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
			if (transformed_is_in_obj(&secnd_ray, father))
			{
				*ray = secnd_ray;
				return (tmp);
			}
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
