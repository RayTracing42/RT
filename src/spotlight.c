/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:25 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/29 17:50:41 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_in_spotlight(t_light *light, t_ray *light_ray)
{
	t_vector	opposite;
	t_spotlight	*s;

	s = (t_spotlight*)light;
	opposite = vector_opposite(s->direction.x, s->direction.y, s->direction.z);
	if (angle_between_vectors(light_ray->equ.vd, opposite) > s->aperture)
		return (0);
	return (1);
}

static t_vector	get_spot_ray_vect(t_dot *pos, t_light *light)
{
	return ((t_vector){((t_spotlight*)light)->orig.x - pos->x,
						((t_spotlight*)light)->orig.y - pos->y,
						((t_spotlight*)light)->orig.z - pos->z});
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
