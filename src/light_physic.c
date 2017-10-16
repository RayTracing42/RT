/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_physic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:42:42 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/16 23:43:07 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>


void		get_col_mix(t_ray *ray, SDL_Color shadows, SDL_Color reflect,
					SDL_Color refract)
{
	double		purcent;
	double		rfl;
	double		rfr;

	rfl = ray->obj->obj_light.reflection_amount;
	rfr = ray->obj->obj_light.refraction_amount;
	purcent = 2 - (rfr + rfl);
	if (rfr == 0)
		get_reflected_col(ray, ray->obj, reflect);
	else if (rfl == 0)
		get_refracted_col(ray, ray->obj, refract);
	else
	{
		ray->color.r = shadows.r * purcent + reflect.r * rfl + refract.r * rfr;
		ray->color.g = shadows.g * purcent + reflect.g * rfl + refract.g * rfr;
		ray->color.b = shadows.b * purcent + reflect.b * rfl + refract.b * rfr;
	}
}

SDL_Color	get_shade_col(t_ray *ray)
{
	double		coef;
	SDL_Color	col;
	t_vector	tmp;

	col = ray->color;
	coef = (vect_dot_product(&ray->equ.vd, &ray->normal) /
			(get_vect_lenght(&ray->equ.vd) * get_vect_lenght(&ray->normal)));
	if (coef < 0)
		coef = 0;
	tmp.x = col.r * coef;
	tmp.y = col.g * coef;
	tmp.z = col.b * coef;
	return ((SDL_Color){tmp.x > 255 ? 255 : tmp.x,
			tmp.y > 255 ? 255 : tmp.y,
			tmp.z > 255 ? 255 : tmp.z, 255});
}
