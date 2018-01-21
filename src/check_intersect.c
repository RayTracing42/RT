/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/21 01:01:12 by fcecilie         ###   ########.fr       */
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
		{
			return (1);
		}
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
	t_ray		res_ray;

	dist = 0;
	tmp_ray.shad_opacity = 0;
	res_ray = *ray;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (lt(tmp, 0))
			tmp_ray = second_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			transform_inter(&tmp_ray, tmp_ray.obj);
			neg_dist = dist;
			limit(&tmp_ray, tmp_ray, tmp, &neg_dist, -1);
			if (gt(neg_dist, 0) && l_objs->obj->negative_obj)
			{
				tmp_ray2 = second_intersect(&tmp_ray, l_objs->obj, &tmp2);
				limit(&tmp_ray2, tmp_ray2, tmp2, &tmp2, neg_dist);
				if (gt(neg_dist = check_negative_intersect(&tmp_ray, l_objs->obj->negative_obj, neg_dist, tmp2), 0))
				{
					if (!(eq(neg_dist, tmp2) && tmp_ray2.limit_status == EMPTY))
						dist = neg_dist;
					if (eq(neg_dist, tmp2) && tmp_ray2.limit_status != EMPTY)
						res_ray = tmp_ray2;
					else if (!eq(neg_dist, tmp2))
						res_ray = tmp_ray;
				}
			}
			else if (gt(neg_dist, 0))
			{
				res_ray = tmp_ray;
				dist = neg_dist;
			}
		}
		l_objs = l_objs->next;
	}
	if (!is_in_front_of_vector(*(t_dot*)&res_ray.equ.vc, res_ray.inter, res_ray.normal))
		res_ray.normal = (t_vector){-res_ray.normal.x, -res_ray.normal.y,
			-res_ray.normal.z};
	*ray = res_ray;
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
