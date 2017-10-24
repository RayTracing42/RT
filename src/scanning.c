/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/10/24 19:48:44 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		tmp;
	double		distance;
	int			nb;
	t_dot		intersect;

	distance = 0;
	while (l_objs != NULL)
	{
		tmp = l_objs->obj->intersect(ray, l_objs->obj);
		if (tmp > 0 && (distance == 0 || (tmp < distance && distance > 0)))
		{
			distance = tmp;
			intersect = ray->inter;
			ray->color = l_objs->obj->color;
			ray->normal = *l_objs->obj->get_normal(&ray->inter, l_objs->obj);
			ray->obj = l_objs->obj;
			ray->percuted_refractive_i = l_objs->obj->obj_light.refractive_index;
			nb = ray->nb_intersect;
		}
		l_objs = l_objs->next;
	}
	ray->inter = intersect;
	ray->nb_intersect = nb;
	return (distance);
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
