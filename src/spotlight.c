/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spotlight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:25 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 14:55:25 by edescoin         ###   ########.fr       */
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
	*dest = (t_vector){spot->orig.x - inter.x, spot->orig.y - inter.y,
						spot->orig.z - inter.z};
}

t_spotlight	*new_spotlight(t_vector direction, t_dot orig, SDL_Color color,
						double aperture)
{
	t_spotlight	*spot;

	spot = (t_spotlight*)new_light(SPOT, direction, color);
	spot->orig = orig;
	spot->aperture = aperture;
	spot->get_ray_vect = get_ray_vect;
	spot->is_in_light = is_in_spotlight;
	return (spot);
}
