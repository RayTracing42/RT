/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:32:56 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 12:54:39 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t	get_type_size(t_type type)
{
	const size_t	sizes[4] = {sizeof(t_cone), sizeof(t_cylinder),
								sizeof(t_plane), sizeof(t_sphere)};
	return (sizes[type]);
}

t_object	*new_object(t_type type, t_dot origin,
	 					t_vector dir, SDL_Color color)
{
	t_object	*obj;

	if (!(obj = malloc(get_type_size(type))))
		exit_error("rt", "malloc");
	*(t_type*)&obj->obj_type = type;
	obj->origin = origin;
	obj->dir = dir;
	obj->color = color;
	obj->get_normal = NULL;
	obj->intersect = NULL;
	return (obj);
}

void		delete_object(t_object *obj)
{
	free(obj);
}
