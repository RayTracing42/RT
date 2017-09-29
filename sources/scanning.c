/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/09/29 14:10:59 by edescoin         ###   ########.fr       */
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
		}
		l_objs = l_objs->next;
	}
	ray->inter = intersect;
	return (distance);
}

int		scanning(t_scene *scn)
{
	int			x;
	int			y;
	double		distance;
	t_ray		ray;

	ray.equ.vc = *(t_vector*)&scn->cam->origin;
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
				view_plane_vector(x, y, scn->cam, &ray.equ.vd);
				distance = check_intersect(&ray, scn->objects);
				if (distance > 0)
				{
					shadows(&ray, scn);
					put_pixel(x, y, &ray.color);
				}
				else
					put_pixel(x, y, &(SDL_Color){0, 0, 0, 255});
		}
	}
	return (0);
}
