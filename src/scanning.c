/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/10/09 19:17:15 by edescoin         ###   ########.fr       */
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
		tmp = l_objs->obj->intersect(ray, l_objs->obj);
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

SDL_Color		effects(t_ray *ray, t_scene *scn)
{
	SDL_Color	reflected;

	if (check_intersect(ray, scn->objects) > 0)
	{
		shadows(ray, scn);
		reflected = reflect(ray, scn);
//		refract(ray, scn);
		get_reflected_col(ray, NULL, reflected);
		/*ray->color.r = (ray->color.r + reflected.r) / 2;f
		ray->color.g = (ray->color.g + reflected.g) / 2;
		ray->color.b = (ray->color.b + reflected.b) / 2;*/
		return (ray->color);
	}
	return (ray->color = (SDL_Color){0, 0, 0, 255});
}

int		scanning(t_scene *scn)
{
	int			x;
	int			y;
	t_ray		ray;

	ray.equ.vc = *(t_vector*)&scn->cam->origin;
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
	return (0);
}
