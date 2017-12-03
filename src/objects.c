/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:32:56 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/26 15:57:44 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t	get_type_size(t_type type)
{
	const size_t	sizes[4] = {sizeof(t_cone), sizeof(t_cylinder),
								sizeof(t_plane), sizeof(t_sphere)};
	return (sizes[type]);
}

t_object		*new_object(t_type type, t_objs_comp args)
{
	t_object	*obj;

	if (!(obj = malloc(get_type_size(type))))
		exit_error("rt", "malloc");
	*(t_type*)&obj->obj_type = type;
	obj->origin = args.orig;
	obj->color = args.col;
	obj->obj_light = (t_obj_phys){args.reflection_amount,
								args.refraction_amount, args.refractive_index,
								args.shininess};
	obj->get_normal = NULL;
	obj->intersect = NULL;
	obj->trans_const = create_identity(4);
	obj->trans_iconst = create_identity(4);
	obj->trans_idir = create_identity(4);
	obj->trans_norm = create_identity(4);
	return (obj);
}

void		set_all_matrix(t_object *object, t_trans_data data)
{
	scale(&object->trans_const, data.scale.x, data.scale.y, data.scale.z);
	x_rotation(&object->trans_const, data.rot.x);
	y_rotation(&object->trans_const, data.rot.y);
	z_rotation(&object->trans_const, data.rot.z);
	translation(&object->trans_const, data.trans.x, data.trans.y, data.trans.z);
	get_inv_4x4mat(object->trans_iconst, object->trans_const);
	scale(&object->trans_idir, data.scale.x, data.scale.y, data.scale.z);
	x_rotation(&object->trans_idir, data.rot.x);
	y_rotation(&object->trans_idir, data.rot.y);
	z_rotation(&object->trans_idir, data.rot.z);
	get_inv_4x4mat(object->trans_idir, object->trans_idir);
	scale(&object->trans_norm, data.scale.x, data.scale.y, data.scale.z);
	get_inv_4x4mat(object->trans_norm, object->trans_norm);
	x_rotation(&object->trans_norm, data.rot.x);
	y_rotation(&object->trans_norm, data.rot.y);
	z_rotation(&object->trans_norm, data.rot.z);
}

void		delete_object(t_object *obj)
{
	if (obj)
	{
		delete_matrix(obj->trans_const);
		delete_matrix(obj->trans_iconst);
		delete_matrix(obj->trans_idir);
		delete_matrix(obj->trans_norm);
		free(obj);
	}
}
