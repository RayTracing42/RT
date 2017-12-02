/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/11/29 04:06:32 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_parequation	transform_equ(t_ray *ray, t_object *obj)
{
	t_parequation	trs;

	trs.vc = (t_vector){ray->equ.vc.x - obj->origin.x, ray->equ.vc.y - obj->origin.y, ray->equ.vc.z - obj->origin.z};
	mult_vect(&trs.vc, obj->trans_iconst, &trs.vc);
	mult_vect(&trs.vd, obj->trans_idir, &ray->equ.vd);
	return (trs);
}

void				transform_inter(t_ray *ray, t_object *obj)
{
	mult_vect(&ray->normal, obj->trans_norm, obj->get_normal(&ray->inter, obj));
	mult_vect((t_vector*)&ray->inter, obj->trans_const, (t_vector*)&ray->inter);
	ray->inter = (t_dot){ray->inter.x + obj->origin.x, ray->inter.y + obj->origin.y, ray->inter.z + obj->origin.z};
}

/*
**	if (first_intersect()
**		if (local_limit()
**			if (transfo()
**				if (global_limit()
**					OK;
**	else if ("mode creux" && second_intersect)
**		if (local_limit()
**			if (transfo()
**				if (global_limit()
**					OK;
**	else if ("mode plein")
**		intersect(local_x) && verification de si le pt en auestion est toujours dans l'objet;
**		intersect(local_y) && verification de si le pt en auestion est toujours dans l'objet;
**		intersect(local_z) && verification de si le pt en auestion est toujours dans l'objet;
**					
**		intersect(global_x) && verification de si le pt en auestion est toujours dans l'objet;
**		intersect(global_y) && verification de si le pt en auestion est toujours dans l'objet;
**		intersect(global_z) && verification de si le pt en auestion est toujours dans l'objet;
**			-> on prend le pt le plus proche. 	
**					
**					
*/

SDL_Color		effects(t_ray *ray, t_scene *scn)
{
	SDL_Color	reflect_ray;
	SDL_Color	refract_ray;

	if (check_intersect(ray, scn->objects) > 0)
	{
		ray->color = shadows(ray, scn);
		reflect_ray = reflect(ray, scn);
		refract_ray = refract(ray, scn);
		get_reflected_col(ray, ray->obj, reflect_ray);
		get_refracted_col(ray, ray->obj, refract_ray);
		return (ray->color);
	}
	return (ray->color = (SDL_Color){0, 0, 0, 255});
}

void	scanning(t_scene *scn)
{
	int			x;
	int			y;
	t_ray		ray;

	ray.equ.vc = *(t_vector*)&scn->cam->origin;
	ray.actual_refractive_i = 1;
	ray.limit = 1;
	ray.l_objs = NULL;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
				view_plane_vector(x, y, scn->cam, &ray.equ.vd);
				effects(&ray, scn);
				put_pixel(x, y, &ray.color);
		}
	}
}
