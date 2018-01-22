/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/22 15:29:57 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_parequation	transform_equ(t_ray *ray, t_object *obj)
{
	t_parequation	trs;

	trs.vc = (t_vector){ray->equ.vc.x - obj->origin.x,
		ray->equ.vc.y - obj->origin.y, ray->equ.vc.z - obj->origin.z};
	mult_vect(&trs.vc, obj->trans_iconst, &trs.vc);
	mult_vect(&trs.vd, obj->trans_idir, &ray->equ.vd);
	return (trs);
}

void			transform_inter(t_ray *ray, t_object *obj)
{
	mult_vect(&ray->normal, obj->trans_norm, &ray->normal);
	mult_vect((t_vector*)&ray->inter, obj->trans_const, (t_vector*)&ray->inter);
	ray->inter = (t_dot){ray->inter.x + obj->origin.x,
		ray->inter.y + obj->origin.y, ray->inter.z + obj->origin.z};
}

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

static void		randomize_cam_orig(t_camera *cam)
{
	if (rand() % 2)
		cam->origin.x += (cam->depth * (rand() % 2001 / 1000));
	else
		cam->origin.x -= (cam->depth * (rand() % 2001 / 1000));
	if (rand() % 2)
		cam->origin.y += (cam->depth * (rand() % 2001 / 1000));
	else
		cam->origin.y -= (cam->depth * (rand() % 2001 / 1000));
	if (rand() % 2)
		cam->origin.z += (cam->depth * (rand() % 2001 / 1000));
	else
		cam->origin.z -= (cam->depth * (rand() % 2001 / 1000));
}

void			scanning(t_scene *scn)
{
	int			x;
	int			y;
	t_ray		ray;
	t_dot		cam_orig;

	cam_orig = scn->cam->origin;
	ray.actual_refractive_i = 1;
	ray.limit = 1;
	ray.tree = add_new_leaf(NULL, NULL, NULL, 0);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			scn->cam->origin = cam_orig;
			randomize_cam_orig(scn->cam);
			ray.equ.vc = *(t_vector*)&scn->cam->origin;
			view_plane_vector(x, y, scn->cam, &ray.equ.vd);
			effects(&ray, scn);
			put_pixel(x, y, &ray.color);
		}
	}
	remove_leaf(ray.tree);
}
