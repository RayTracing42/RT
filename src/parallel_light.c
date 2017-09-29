/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:46:09 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/29 15:25:04 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int			is_in_parallel_light(t_vector dir)
{
	(void)dir;
	return (1);
}

static t_vector		get_par_ray_vect(t_vector *pos, t_light *light)
{
	(void)pos;
	return ((t_vector){-light->direction.x,
						-light->direction.y,
						-light->direction.z});
}

t_parallel_light	*new_parallel_light(t_vector direction, SDL_Color color)
{
	t_parallel_light	*par;

	par = (t_parallel_light*)new_light(PARALLEL, direction, color);
	par->get_ray_vect = get_par_ray_vect;
	par->is_in_light = is_in_parallel_light;
	return (par);
}

void				delete_parallel_light(t_parallel_light *par)
{
	delete_light((t_light*)par);
}
