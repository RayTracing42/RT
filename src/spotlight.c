/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:25 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 15:35:51 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_in_spotlight(t_vector dir)
{
	//À modifier
	(void)dir;
	return (0);
}

static t_vector	get_spot_ray_vect(t_vector *pos, t_light *light)
{
	return ((t_vector){((t_spotlight*)light)->orig.x - pos->x,
						((t_spotlight*)light)->orig.y - pos->y,
						((t_spotlight*)light)->orig.z - pos->z});
}

t_spotlight	*new_spotlight(t_vector direction, t_dot orig, SDL_Color color,
						double aperture)
{
	t_spotlight	*spot;

	if (aperture == 360)
		spot = (t_spotlight*)new_light(ORB, direction, color);
	else
		spot = (t_spotlight*)new_light(SPOT, direction, color);
	spot->orig = orig;
	spot->aperture = aperture;
	spot->get_ray_vect = &get_spot_ray_vect;
	spot->is_in_light = &is_in_spotlight;
	return (spot);
}

void		delete_spotlight(t_spotlight *spot)
{
	delete_light((t_light*)spot);
}
