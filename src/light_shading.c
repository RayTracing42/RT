/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:42:42 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/09 11:32:05 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

SDL_Color	get_shade_col(t_ray *ray)
{
	double		coef;
	SDL_Color	*col;
	t_vector	tmp_col;

	col = &ray->color;
	coef = (vect_dot_product(ray->equ.vd, ray->normal) /
		(get_vect_lenght(&ray->equ.vd) * get_vect_lenght(&ray->normal)));
	if (coef < 0)
		coef = 0;
	tmp_col.x = col->r * coef;
	tmp_col.y = col->g * coef;
	tmp_col.z = col->b * coef;
	return ((SDL_Color){tmp_col.x > 255 ? 255 : tmp_col.x,
						tmp_col.y > 255 ? 255 : tmp_col.y,
						tmp_col.z > 255 ? 255 : tmp_col.z, 255});
}

SDL_Color	get_specular_col(t_ray *ray, t_ray *light_ray)
{
	t_vector	r;
	t_vector	v;
	t_vector	tmp_col;
	double		coef;

	r = get_reflected_vect(&ray->equ.vd, &ray->normal);
	vect_normalize(&r);
	v = light_ray->equ.vd;
	vect_normalize(&v);
	coef = ray->obj->obj_light.shininess ? (light_ray->light->power *
		pow(vect_dot_product(r, v), ray->obj->obj_light.shininess)) : 0;
	tmp_col.x = light_ray->light->color.r * coef;
	tmp_col.y = light_ray->light->color.g * coef;
	tmp_col.z = light_ray->light->color.b * coef;
	return ((SDL_Color){tmp_col.x > 255 ? 255 : tmp_col.x,
						tmp_col.y > 255 ? 255 : tmp_col.y,
						tmp_col.z > 255 ? 255 : tmp_col.z, 255});
}
