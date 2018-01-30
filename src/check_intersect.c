/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 05:26:14 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/30 05:57:15 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/30 05:25:47 by fcecilie         ###   ########.fr       */
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
		basic->a.nb_intersect = 0;
		basic->b.nb_intersect = 0;
		return (0);
	}
}

void	choice_intersect(t_list_ray *l, t_ray *ray, double *dist)
{
	while (l)
	{
		if (eq(*dist, 0) || (gt(*dist, 0) && lt(l->t, *dist)))
		{
			if (l->r.obj->status != EMPTY)
			{
				*dist = l->t;
				*ray = l->r;
			}
		}
		delete_cell_ray(&l);
//		l = l->next;
	}
}

double	check_intersect(t_ray *ray, t_list_objs *l)
{
	double			dist;
	t_couple_ray	basic;
	t_couple_ray	lim;
	t_couple_ray	neg;
	t_list_ray		*l_ray;
	
	dist = 0;
	while (l)
	{
	basic.a.nb_intersect = 0;
	basic.b.nb_intersect = 0;
	lim.a.nb_intersect = 0;
	lim.b.nb_intersect = 0;
	neg.a.nb_intersect = 0;
	neg.b.nb_intersect = 0;
		basic.a = first_intersect(ray, l->obj, &basic.ta);
		basic.b = second_intersect(ray, l->obj, &basic.tb);
		if (basic.a.nb_intersect > 0 && basic.b.nb_intersect > 0)
		{
			l_ray = NULL;
			transform_inter(&basic.a, l->obj);
			transform_inter(&basic.b, l->obj);
			if (l->obj->limit)
				lim = limit(l->obj, ray);
			if (l->obj->negative_obj)
				neg = negative_obj(&basic, l->obj, ray);
			unvalid_point_in_limit(&basic, l->obj);
			unvalid_point_in_negative_obj(&basic, l->obj, ray);
			if (l->obj->limit)
				unvalid_point_in_negative_obj(&lim, l->obj, ray);
			add_cell_ray(&l_ray, &basic);
			add_cell_ray(&l_ray, &lim);
			add_cell_ray(&l_ray, &neg);
			choice_intersect(l_ray, ray, &dist);
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
