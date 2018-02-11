/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/11 11:46:26 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_obj(const double t, const t_dot inter, t_object *obj)
{
	double	tmp;
	t_ray	ray;

	ray.equ = (t_parequation){*(t_vector*)&inter, (t_vector){0.01, 0.0001, 0.01}};
	first_intersect(&ray, obj, &tmp);
	if (le(tmp, t))
	{
		second_intersect(&ray, obj, &tmp);
		if (le(t, tmp))
			return (1);
	}
	return (0);
}

int		is_in_limited_obj(const double *t, const t_ray *ray, t_object *obj)
{
	double	t_tmp;
	t_ray	tmp;

	tmp.equ = (t_parequation){*(t_vector*)&ray->inter, (t_vector){0, 0, 0.01}};
	first_intersect(&tmp, obj, &t_tmp);
	if (le(t_tmp, *t))
	{
		second_intersect(&tmp, obj, &t_tmp);
		if (le(*t, t_tmp))
		{
			if (obj->limit)
			{
				if (is_in_limit(ray, obj))
					return (1);
			}
			else
				return (1);
		}
	}
	return (0);
}

void	choice_intersect(t_list_ray *l, t_ray *ray, double *dist)
{
	while (l)
	{
		if (l->r.nb_intersect > 0)
		{
			if (eq(*dist, 0) || (gt(*dist, 0) && lt(l->t, *dist)))
			{
				if (l->r.obj->status != EMPTY)
				{
					*dist = l->t;
					*ray = l->r;
				}
			}
		}
		delete_cell_ray(&l);
	}
}

double			check_intersect(t_ray *ray, t_list_objs *l, int check_lights)
{
	double			dist;
	t_couple_ray	basic;
	t_list_ray		*l_ray;

	dist = 0;
	while (l)
	{
		if (!l->obj->is_light || check_lights)
		{
			basic.a = first_intersect(ray, l->obj, &basic.ta);
			basic.b = second_intersect(ray, l->obj, &basic.tb);
			if (basic.a.nb_intersect > 0 && basic.b.nb_intersect > 0)
			{
				l_ray = NULL;
				transform_inter(&basic.a, l->obj);
				transform_inter(&basic.b, l->obj);
				if (l->obj->limit)
					limit(&basic, l->obj, ray);
				if (l->obj->negative_obj)
					negative_obj(&l_ray, &basic, l->obj, ray);
				add_cell_ray(&l_ray, &basic.a, &basic.ta);
				add_cell_ray(&l_ray, &basic.b, &basic.tb);
				choice_intersect(l_ray, ray, &dist);
			}
		}
		l = l->next;
	}
	correct_normal(*(t_dot*)&ray->equ.vc, ray->inter, &ray->normal);
	return (dist);
}

t_ray	first_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray			tmp_ray;
	t_parequation	e;

	tmp_ray = *ray;
	tmp_ray.obj = obj;
	e = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, e, obj, 1);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.normal = tmp_ray.obj->get_normal(&tmp_ray.inter, tmp_ray.obj);
	if (obj->texture == NULL)
		tmp_ray.color = obj->color;
	else
		tmp_ray.color = getTextColor(e, *tmp, obj);
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}

t_ray	second_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;
	t_parequation	e;

	tmp_ray = *ray;
	tmp_ray.obj = obj;
	e = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, e, obj, 2);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.normal = tmp_ray.obj->get_normal(&tmp_ray.inter, tmp_ray.obj);
	tmp_ray.normal = (t_vector){-tmp_ray.normal.x, -tmp_ray.normal.y,
		-tmp_ray.normal.z};
	if (obj->texture == NULL)
		tmp_ray.color = obj->color;
	else
		tmp_ray.color = getTextColor(e, *tmp, obj);
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}
