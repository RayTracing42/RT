/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:25 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 15:05:08 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_in_spotlight(t_vector dir)
{
	//À modifier
	(void)dir;
	return (0);
}

static void	get_ray_vect(t_spotlight *spot, t_vector *dest, t_dot inter)
{
	*dest = (t_vector){spot->origin.x - inter.x, spot->origin.y - inter.y,
						spot->origin.z - inter.z};
}

t_spotlight	*new_spotlight(t_vector direction, t_dot origin, SDL_Color color,
						double aperture)
{
	t_spotlight	*spot;

	spot = (t_spotlight*)new_light(SPOT, direction, color);
	spot->origin = origin;
	spot->aperture = aperture;
	spot->get_ray_vect = get_ray_vect;
	spot->is_in_light = is_in_spotlight;
	return (spot);
}

void		delete_spotlight(t_spotlight *spot)
{
	delete_light((t_light*)spot);
}
