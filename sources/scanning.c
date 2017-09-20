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
	t_vector	cam_pixel;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			//	recuperer le vecteur directeur unitaire camera -> pixel;
				view_plane_vector(x, y, scn->cam, &cam_pixel);
				printf("vecteur camera -> pixel pour x = %d et y = %d --> (%.2f ; %.2f ; %.2f)\n", x, y, cam_pixel.x, cam_pixel.y, cam_pixel.z);
			//	tester les objs pour verifier si l'un d'eux est sur la route du rayon;
				distance = check_intersect(&ray, scn->objects);
				distance = (double)distance;
			//	si un objet a ete rencontre, tester les lumieres et differents effets;
			x++;
		}
		y++;
	}
	return (0);
}
