/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/09/06 00:52:44 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	t_list_objs	*first;
	double		tmp;
	double		distance;

	distance = -1;
	first = l_objs;
	while (l_objs != NULL)
	{
		tmp = -1;
		tmp = l_objs->obj->intersect(ray, l_objs->obj);
		if (tmp != -1 && (distance == -1 || (tmp < distance && distance > 0)))
		{
			distance = tmp;
			//	il faut garder en memoire l'addresse de l'obj que le ray a rencontre;
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
		//		printf("distance = %f\n", distance);
				if (distance > 0)
					put_pixel(x, y, &(SDL_Color){255, 255, 255, 255});
				else
					put_pixel(x, y, &(SDL_Color){0, 0, 0, 0});
			//	si un obje a ete rencontre, tester les lumieres et differents effets;
			x++;
		}
		y++;
	}
	return (0);
}
