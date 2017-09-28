/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/09/28 16:15:05 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	t_list_objs	*first;
	double		tmp;
	double		distance;

	distance = 0;
	first = l_objs;
	while (l_objs != NULL)
	{
		tmp = l_objs->obj->intersect(ray, l_objs->obj);
		if (tmp > 0 && (distance == 0 || (tmp < distance && distance > 0)))
		{
			distance = tmp;
			ray->color = l_objs->obj->color;
			l_objs->obj->get_normal(&ray->inter, l_objs->obj);
			ray->normal = vector(l_objs->obj->normal.x, l_objs->obj->normal.x, l_objs->obj->normal.z);
		}
		l_objs = l_objs->next;
	}
	l_objs = first;
	return (distance);
}

int		scanning(t_scene *scn)
{
	int			x;
	int			y;
	double		distance;
	t_ray		ray;

	ray.equ.vc = vector(scn->cam->origin.x, scn->cam->origin.y,
			scn->cam->origin.z);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
				view_plane_vector(x, y, scn->cam, &ray.equ.vd);
				distance = check_intersect(&ray, scn->objects);

				if (distance > 0)
				{
					shadows(&ray, scn);
					put_pixel(x, y, &ray.color);
				}
				else
					put_pixel(x, y, &(SDL_Color){0, 0, 0, 0});
			x++;
		}
		y++;
	}
	return (0);
}
