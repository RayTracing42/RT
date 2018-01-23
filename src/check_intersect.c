/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/23 04:46:21 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_obj(const double t, const t_dot inter, t_object *obj)
{
	double	tmp;
	t_ray	ray;

	ray.equ = (t_parequation){*(t_vector*)&inter, (t_vector){0, 0, 0.01}};
	first_intersect(&ray, obj, &tmp);
	if (le(tmp, t))
	{
		second_intersect(&ray, obj, &tmp);
		if (le(t, tmp))
			return (1);
	}
	return (0);
}

double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		dist;
	double		neg_dist;
	double		tmp;
	double		tmp2;
	t_ray		tmp_ray;
	t_ray		tmp_ray2;
	t_ray		tmp_ray3;

	dist = 0;
	tmp_ray.shad_opacity = 0;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (lt(tmp, 0))
			tmp_ray = second_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			neg_dist = dist;
			transform_inter(&tmp_ray, l_objs->obj);
			limit(&tmp_ray, tmp_ray, tmp, &neg_dist, NULL);
			tmp_ray3 = tmp_ray;
			if (gt(neg_dist, 0) && l_objs->obj->negative_obj)
			{
				tmp_ray2 = second_intersect(ray, l_objs->obj, &tmp2);
				transform_inter(&tmp_ray2, l_objs->obj);
				limit(&tmp_ray2, tmp_ray2, tmp2, &tmp2, &neg_dist);
				if ((neg_dist = check_negative_intersect(&tmp_ray, l_objs->obj->negative_obj, neg_dist, tmp2) > 0))
				{
					if (!(eq(neg_dist, tmp2) && tmp_ray2.limit_status == EMPTY))
						dist = neg_dist;
					if (eq(neg_dist, tmp2) && tmp_ray2.limit_status != EMPTY)
						*ray = tmp_ray2;
					else if (!eq(neg_dist, tmp2))
						*ray = tmp_ray.obj ? tmp_ray : tmp_ray3;
				}
			}
			else if (gt(neg_dist, 0))
			{
				*ray = tmp_ray3;
				dist = neg_dist;
			}
		}
		l_objs = l_objs->next;
	}
	if (!is_in_front_of_vector(*(t_dot*)&ray->equ.vc, ray->inter, ray->normal))
		ray->normal = (t_vector){-ray->normal.x, -ray->normal.y,
			-ray->normal.z};
	return (dist);
}

t_ray	first_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	tmp_ray.obj = obj;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 1);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.normal = *tmp_ray.obj->get_normal(&tmp_ray.inter, tmp_ray.obj);
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}

t_ray	second_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	tmp_ray.obj = obj;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 2);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.normal = *tmp_ray.obj->get_normal(&tmp_ray.inter, tmp_ray.obj);
	tmp_ray.normal = (t_vector){-tmp_ray.normal.x, -tmp_ray.normal.y,
		-tmp_ray.normal.z};
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}
