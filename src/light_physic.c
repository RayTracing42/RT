/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_physic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:42:42 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/26 19:49:46 by edescoin         ###   ########.fr       */
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
