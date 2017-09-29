/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:25 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/28 20:08:58 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_in_spotlight(t_spotlight *s, t_vector light_ray)
{
	t_vector	opposite;

	opposite = vector_opposite(s->direction.x, s->direction.y, s->direction.z);
	if (angle_between_vectors(light_ray, opposite) > s->aperture)
		return (0);
	return (1);
}

static t_vector	get_spot_ray_vect(t_vector inter, t_spotlight *light)
{
	return ((t_vector){light->orig.x - inter.x, light->orig.y - inter.y,
						light->orig.z - inter.z});
}

t_spotlight	*new_spotlight(t_vector direction, t_dot origin, SDL_Color color,
						double aperture)
{
	t_spotlight	*spot;

	spot = (t_spotlight*)new_light(SPOT, direction, color);
	spot->orig = origin;
	spot->aperture = aperture;
	spot->get_ray_vect = get_spot_ray_vect;
	spot->is_in_light = is_in_spotlight;
	return (spot);
}

void		delete_spotlight(t_spotlight *spot)
{
	delete_light((t_light*)spot);
}
