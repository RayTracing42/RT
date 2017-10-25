/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 13:51:24 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 17:03:10 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static size_t	get_type_size(t_light_type type)
{
	const size_t	sizes[3] = {sizeof(t_orb_light),
								sizeof(t_parallel_light),
								sizeof(t_spotlight)};

	return (sizes[type]);
}

t_light			*new_light(t_light_type type, t_vector direction,
							SDL_Color color)
{
	t_light	*light;

	if (!(light = malloc(get_type_size(type))))
		exit_error("rt", "malloc");
	*(t_light_type*)&light->type = type;
	light->direction = direction;
	light->color = color;
	light->get_ray_vect = NULL;
	light->is_in_light = NULL;
	return (light);
}

void			delete_light(t_light *light)
{
	free(light);
}
