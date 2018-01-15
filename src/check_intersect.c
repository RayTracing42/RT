/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/15 16:50:23 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		is_in_obj(double t, t_ray *ray, t_object *obj)
{
	double	tmp;


	first_intersect(ray, obj, &tmp);
	//printf("%f, %f\n", tmp, t);
	if (lt(tmp, t))
	{
		second_intersect(ray, obj, &tmp);
		if (lt(t, tmp))
			return (1);
	}
	/*second_intersect(ray, obj, &tmp);
	printf("%f, %f\n\n", tmp, t);*/
	return (0);
}

/*
int		is_in_obj(t_dot *inter, t_ray *ray, t_object *obj)
{
	t_ray	first;
	t_ray	second;
	double	a;
	double	b;
	double	c;
	double	tmp;

	if (ray->obj != obj)
	{
		first = first_intersect(ray, obj, &tmp);
		if (tmp)
		{
			transform_inter(&first, obj);
			c = get_dot_dist(inter, (t_dot*)&ray->equ.vc);
			a = get_dot_dist(&first.inter, (t_dot*)&ray->equ.vc);
			if (a <= c)
			{
				second = second_intersect(ray, obj, &tmp);
				if (tmp)
				{
					transform_inter(&second, obj);
					b = get_dot_dist(&second.inter, (t_dot*)&ray->equ.vc);
					if (c <= b)
						return (1);
				}
			}
		}
	}
	return (0);
}
*/

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
	res_ray = *ray;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			transform_inter(&tmp_ray, tmp_ray.obj);
/*
			// FLAVIAN
			neg_dist = dist;
			limit(&res_ray, &tmp_ray, &tmp, &neg_dist);
			check_negative_obj_intersect(&res_ray, l_objs->obj, &neg_dist);
			if (!(neg_dist == 0))
				dist = neg_dist;
			// FLAVIAN
*/

/**/
			// EMERIC
			neg_dist = dist;
			limit(&tmp_ray, tmp_ray, tmp, &neg_dist, 1);
			if (gt(neg_dist, 0) && l_objs->obj->negative_obj)
			{
				tmp_ray2 = second_intersect(&tmp_ray, l_objs->obj, &tmp2);
				limit(&tmp_ray2, tmp_ray2, tmp2, &tmp2, 2);
				if (gt(neg_dist = check_negative_intersect(&tmp_ray, l_objs->obj->negative_obj, neg_dist, tmp2), 0))
				{
					if (!eq(neg_dist, tmp2) || tmp_ray2.limit_status != EMPTY)
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
			// EMERIC
/**/
		}
		l_objs = l_objs->next;
	}
	*ray = res_ray;
	return (dist);
}

t_ray	first_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 1);
	tmp_ray.normal = *obj->get_normal(&tmp_ray.inter, obj);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}

t_ray	second_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 2);
	tmp_ray.normal = *obj->get_normal(&tmp_ray.inter, obj);
	tmp_ray.normal = (t_vector){-tmp_ray.normal.x, -tmp_ray.normal.y,
		-tmp_ray.normal.z};
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}
