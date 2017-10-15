/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/10/09 19:03:21 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		tmp;
	double		distance;
	t_dot		intersect;

	distance = 0;
	while (l_objs != NULL)
	{
		tmp = l_objs->obj->intersect(ray, l_objs->obj, 1);
		if (tmp > 0 && (distance == 0 || (tmp < distance && distance > 0)))
		{
			distance = tmp;
			intersect = ray->inter;
			ray->color = l_objs->obj->color;
			ray->normal = *l_objs->obj->get_normal(&ray->inter, l_objs->obj);
			ray->obj = l_objs->obj;
		}
		l_objs = l_objs->next;
	}
	ray->inter = intersect;
	return (distance);
}

SDL_Color		effects(t_ray *ray, t_scene *scn, int n)
{
	SDL_Color	reflect_ray;
	SDL_Color	refract_ray;
	SDL_Color	shadows_ray;

	if (check_intersect(ray, scn->objects) > 0)
	{
		shadows_ray = shadows(ray, scn);
		reflect_ray = reflect(ray, scn, n);
		refract_ray = refract(ray, scn, n);
//		get_col_mix(ray, shadows_ray, reflect_ray, refract_ray);
/**/
		ray->color = shadows_ray;
		get_reflected_col(ray, ray->obj, reflect_ray);
		get_refracted_col(ray, ray->obj, refract_ray);
/**/
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
	ray.refractive_index = 1;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
				view_plane_vector(x, y, scn->cam, &ray.equ.vd);
				effects(&ray, scn, 0);
				put_pixel(x, y, &ray.color);
		}
	}
}
