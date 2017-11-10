/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:32:56 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/10 13:42:16 by shiro            ###   ########.fr       */
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
	obj->dir = args.dir;
	obj->color = args.col;
	obj->obj_light = (t_obj_phys){args.reflection_amount,
								args.refraction_amount, args.refractive_index,
								args.shininess};
	obj->get_normal = NULL;
	obj->intersect = NULL;
	obj->rot = create_identity(4);
	obj->rot_inv = create_identity(4);
	obj->trans = create_identity(4);
	obj->trans_inv = create_identity(4);
	obj->scale = create_identity(4);
	obj->scale_inv = create_identity(4);
	translation(&obj->trans, args.orig.x, args.orig.y, args.orig.z);
	translation(&obj->trans_inv, -args.orig.x, -args.orig.y, -args.orig.z);
	return (obj);
}

void		delete_object(t_object *obj)
{
	if (obj)
	{
		delete_matrix(obj->rot);
		delete_matrix(obj->rot_inv);
		delete_matrix(obj->trans);
		delete_matrix(obj->trans_inv);
		delete_matrix(obj->scale);
		delete_matrix(obj->scale_inv);
		free(obj);
	}
}
