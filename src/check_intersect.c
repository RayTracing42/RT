/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/25 17:06:42 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
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
*/

int		non_inverted_intersect(t_couple_ray *basic, t_couple_ray *modified,
		int check)
{
	if (modified->ta <= modified->tb && check == 0)
	{
		*basic = *modified;
		return (1);
	}
	else
	{
		basic->ta = 0;
		basic->tb = 0;
		return (0);
	}
}

double	check_intersect(t_ray *ray, t_list_objs *l)
{
	double			dist;
	t_couple_ray	basic;

	dist = 0;
	while (l)
	{
		basic.a = first_intersect(ray, l->obj, &basic.ta);
		basic.b = second_intersect(ray, l->obj, &basic.tb);
		if (basic.ta != -1 && basic.tb != -1)
		{
			transform_inter(&basic.a, l->obj);
			transform_inter(&basic.b, l->obj);
			if (l->obj->limit)
				limit(&basic, l->obj, ray);
			if (l->obj->negative_obj)
				negative_obj(&basic, l->obj, ray);
			if (gt(basic.ta, 0) && gt(basic.tb, 0))
			{
				if (eq(dist, 0) || (gt(dist, 0) && lt(basic.ta, dist)))
					valid_ray(ray, &dist, &basic.a, &basic.ta);
			}
			else if (le(basic.ta, 0) && gt(basic.tb, 0))
			{
				if (eq(dist, 0) || (gt(dist, 0) && lt(basic.tb, dist)))
					valid_ray(ray, &dist, &basic.b, &basic.tb);
			}
		}
		l = l->next;
	}
	is_in_front_of_vector(*(t_dot*)&ray->equ.vc, ray->inter, &ray->normal);
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
