/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_physic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:42:42 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/27 17:54:27 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	get_reflected_vect(t_vector *dir, const t_vector *norm)
{
	double	cos_theta1;

	cos_theta1 = vect_dot_product(norm, &(t_vector){-dir->x, -dir->y, -dir->z});
	dir->x += 2 * cos_theta1 * norm->x;
	dir->y += 2 * cos_theta1 * norm->y;
	dir->z += 2 * cos_theta1 * norm->z;
}

void	get_refracted_vect(t_vector *dir, const t_vector *norm,
				t_object *src, t_object *dst)
{
	double	cos_theta1;
	double	cos_theta2;
	double	n1_by_n2;

	cos_theta1 = vect_dot_product(norm, &(t_vector){-dir->x, -dir->y, -dir->z});
	n1_by_n2 = src->obj_light.refractive_index /
			dst->obj_light.refractive_index;
	cos_theta2 = sqrt(1 - pow(n1_by_n2, 2) * (1 - pow(cos_theta1, 2)));
	dir->x = n1_by_n2 * dir->x + (n1_by_n2 * cos_theta1 - cos_theta2) * norm->x;
	dir->y = n1_by_n2 * dir->y + (n1_by_n2 * cos_theta1 - cos_theta2) * norm->y;
	dir->z = n1_by_n2 * dir->z + (n1_by_n2 * cos_theta1 - cos_theta2) * norm->z;
}

void	get_reflected_col(t_ray *ray, t_object *src,
				SDL_Color reflected_obj_col)
{
	ray->color.r *= (reflected_obj_col.r /
			(src->obj_light.reflection_amount * 255));
	ray->color.g *= (reflected_obj_col.g /
			(src->obj_light.reflection_amount * 255));
	ray->color.b *= (reflected_obj_col.b /
			(src->obj_light.reflection_amount * 255));
}

void	get_refracted_col(t_ray *ray, t_object *src,
				SDL_Color refracted_obj_col)
{
	ray->color.r *= (refracted_obj_col.r /
			(src->obj_light.refraction_amount * 255));
	ray->color.g *= (refracted_obj_col.g /
			(src->obj_light.refraction_amount * 255));
	ray->color.b *= (refracted_obj_col.b /
			(src->obj_light.refraction_amount * 255));
}

SDL_Color	get_shade_col(t_ray *ray, const t_scene *scene)
{
	double		coef;
	SDL_Color	col;
	t_vector	tmp;

	col = ray->color;
	coef = (vect_dot_product(&ray->equ.vd, &ray->normal) /
			(get_vect_lenght(&ray->equ.vd) * get_vect_lenght(&ray->normal)));
	if (coef < 0)
		coef = 0;
	tmp.x = col.r * ((scene->brightness / 2.0) + (coef * 2.0));
	tmp.y = col.g * ((scene->brightness / 2.0) + (coef * 2.0));
	tmp.z = col.b * ((scene->brightness / 2.0) + (coef * 2.0));
	return ((SDL_Color){tmp.x > 255 ? 255 : tmp.x,
			tmp.y > 255 ? 255 : tmp.y,
			tmp.z > 255 ? 255 : tmp.z, 255});
}
