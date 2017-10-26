/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:42:42 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/26 19:42:46 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

SDL_Color	get_shade_col(t_ray *ray, const t_scene *scene)
{
	double		coef;
	SDL_Color	*col;
	t_vector	tmp;

	col = &ray->color;
	coef = (vect_dot_product(&ray->equ.vd, &ray->normal) /
		(get_vect_lenght(&ray->equ.vd) * get_vect_lenght(&ray->normal)));
	if (coef < 0)
		coef = 0;
	tmp.x = col->r * coef + scene->brightness;
	tmp.y = col->g * coef + scene->brightness;
	tmp.z = col->b * coef + scene->brightness;
	return ((SDL_Color){tmp.x > 255 ? 255 : tmp.x,
						tmp.y > 255 ? 255 : tmp.y,
						tmp.z > 255 ? 255 : tmp.z, 255});
}
