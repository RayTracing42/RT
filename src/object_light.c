/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 11:53:24 by shiro             #+#    #+#             */
/*   Updated: 2018/02/04 12:13:56 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_vector	get_cone_ray_vect(t_dot pos, t_obj_light *obl)
{
	t_dot		res;
	double		tana2;
	double		t;

	res = (t_dot){pos.x - obl->shape->origin.x, pos.y - obl->shape->origin.y,
				pos.z - obl->shape->origin.z};
	mult_vect((t_vector*)&res, obl->shape->trans_iconst, (t_vector*)&res);
	tana2 = ((t_cone*)obl->shape)->tanalpha2;
	t = (pos.x * pos.x + pos.z * pos.z) / (pos.y * pos.y * tana2);

	if (((t_cone*)obl->shape)->upper)
		t = (-1 - t * tana2 + sqrt(t * (2 * tana2 + tana2 * tana2 + 1))) / (2 * (1 - t * tana2 * tana2));
	else
		t = (-1 - t * tana2 - sqrt(t * (2 * tana2 + tana2 * tana2 + 1))) / (2 * (1 - t * tana2 * tana2));
	if (eq(t, 1 / (2 * tana2)))
		return ((t_vector){0, 0, 0});

	mult_vect((t_vector*)&res, obl->shape->trans_const, &(t_vector){res.x / (1 + 2 * t), res.y / (1 - 2 * tana2 * t), res.z / (1 + 2 * t)});
	res = (t_dot){res.x + obl->shape->origin.x, res.y + obl->shape->origin.y,
			res.z + obl->shape->origin.z};
	return ((t_vector){res.x - pos.x, res.y - pos.y, res.z - pos.z});
}

static t_vector	get_cylinder_ray_vect(t_dot pos, t_obj_light *obl)
{
	t_dot		res;
	double		t;
	double		r;

	res = (t_dot){pos.x - obl->shape->origin.x, pos.y - obl->shape->origin.y,
				pos.z - obl->shape->origin.z};
	mult_vect((t_vector*)&res, obl->shape->trans_iconst, (t_vector*)&res);
	if (eq(res.x, 0) && eq(res.y, 0) && eq(res.z, 0))
		return ((t_vector){0, 0, 0});

	r = ((t_sphere*)obl->shape)->radius;
	t = -0.5 + sqrt(res.x * res.x + res.z * res.z) / (2 * r);

	mult_vect((t_vector*)&res, obl->shape->trans_const, &(t_vector){res.x / (1 + 2 * t), res.y, res.z / (1 + 2 * t)});
	res = (t_dot){res.x + obl->shape->origin.x, res.y + obl->shape->origin.y,
			res.z + obl->shape->origin.z};
	return ((t_vector){res.x - pos.x, res.y - pos.y, res.z - pos.z});
}

static t_vector	get_plane_ray_vect(t_dot pos, t_obj_light *obl)
{
	t_dot		res;
	t_vector	n;
	double		t;

	res = (t_dot){pos.x - obl->shape->origin.x, pos.y - obl->shape->origin.y,
				pos.z - obl->shape->origin.z};
	mult_vect((t_vector*)&res, obl->shape->trans_iconst, (t_vector*)&res);
	if (eq(res.x, 0) && eq(res.y, 0) && eq(res.z, 0))
		return ((t_vector){0, 0, 0});
	n = ((t_plane*)obl->shape)->normal;
	t = (n.x * res.x + n.y * res.y + n.z * res.z) /
		(n.x * n.x + n.y * n.y + n.z * n.z);

	mult_vect((t_vector*)&res, obl->shape->trans_const, &(t_vector){res.x - n.x * t, res.y - n.y * t, res.z - n.z * t});
	res = (t_dot){res.x + obl->shape->origin.x, res.y + obl->shape->origin.y,
			res.z + obl->shape->origin.z};
	return ((t_vector){res.x - pos.x, res.y - pos.y, res.z - pos.z});
}

static t_vector	get_sphere_ray_vect(t_dot pos, t_obj_light *obl)
{
	t_dot		res;
	double		t;
	double		r;

	res = (t_dot){pos.x - obl->shape->origin.x, pos.y - obl->shape->origin.y,
				pos.z - obl->shape->origin.z};
	mult_vect((t_vector*)&res, obl->shape->trans_iconst, (t_vector*)&res);
	if (eq(res.x, 0) && eq(res.y, 0) && eq(res.z, 0))
		return ((t_vector){0, 0, 0});

	r = ((t_sphere*)obl->shape)->radius;
	t =  -0.5 + sqrt(res.x * res.x + res.y * res.y + res.z * res.z) / (2 * r);

	mult_vect((t_vector*)&res, obl->shape->trans_const, &(t_vector){res.x / (1 + 2 * t), res.y / (1 + 2 * t), res.z / (1 + 2 * t)});
	res = (t_dot){res.x + obl->shape->origin.x, res.y + obl->shape->origin.y,
			res.z + obl->shape->origin.z};
	return ((t_vector){res.x - pos.x, res.y - pos.y, res.z - pos.z});
}

static t_vector	get_obj_ray_vect(t_dot pos, t_light *light)
{
	t_obj_light	*obl;

	obl = (t_obj_light*)light;
	if (obl->shape->obj_type == SPHERE)
		return (get_sphere_ray_vect(pos, obl));
	else if (obl->shape->obj_type == CONE)
		return (get_cone_ray_vect(pos, obl));
	else if (obl->shape->obj_type == CYLINDER)
		return (get_cylinder_ray_vect(pos, obl));
	else if (obl->shape->obj_type == PLANE)
		return (get_plane_ray_vect(pos, obl));
	else
		return ((t_vector){obl->shape->origin.x - pos.x,
							obl->shape->origin.y - pos.y,
							obl->shape->origin.z - pos.z});
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
