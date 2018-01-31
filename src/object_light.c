/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:53:24 by shiro             #+#    #+#             */
/*   Updated: 2018/01/31 13:15:13 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector	get_obj_ray_vect(t_dot pos, t_light *light)
{
	t_obj_light	*obl;
	t_dot		res;
	double		t;
	double		r;

	obl = (t_obj_light*)light;
	res = (t_dot){pos.x - obl->shape->origin.x, pos.y - obl->shape->origin.y,
				pos.z - obl->shape->origin.z};
	mult_vect((t_vector*)&res, obl->shape->trans_iconst, (t_vector*)&res);
	if (eq(res.x, 0) && eq(res.y, 0) && eq(res.z, 0))
		return ((t_vector){0, 0, 0});

	r = ((t_sphere*)obl->shape)->radius;
	t = sqrt(res.x * res.x + res.y * res.y + res.z * res.z) / (3 * r);

	mult_vect((t_vector*)&res, obl->shape->trans_const, &(t_vector){res.x / (3 * t), res.y / (3 * t), res.z / (3 * t)});
	res = (t_dot){res.x + obl->shape->origin.x, res.y + obl->shape->origin.y,
			res.z + obl->shape->origin.z};
	return ((t_vector){res.x - pos.x, res.y - pos.y, res.z - pos.z});
}

static int		is_in_obj_light(t_light *light, t_ray *light_ray)
{
	(void)light;
	(void)light_ray;
	return (1);
}

t_obj_light		*new_obj_light(double power, t_object *obj)
{
	t_obj_light	*obl;

	obl = (t_obj_light*)new_light(OBJECT, (t_vector){0, 0, 0}, obj->color, power);
	obj->is_light = 1;
	obl->shape = obj;
	obl->is_in_light = is_in_obj_light;
	obl->get_ray_vect = get_obj_ray_vect;
	return (obl);
}

void			delete_obj_light(t_obj_light *obl)
{
	delete_light((t_light*)obl);
}
