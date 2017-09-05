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
//		if (l_objs->obj->obj_type == BOX)
//			box_intersect(ray, (t_box*)l_objs->obj);
		if (l_objs->obj->obj_type == CONE)
			tmp = cone_intersect(ray, (t_cone*)l_objs->obj);
		if (l_objs->obj->obj_type == CYLINDER)
			tmp = cylinder_intersect(ray, (t_cylinder*)l_objs->obj);
		if (l_objs->obj->obj_type == PLANE)
			tmp = plane_intersect(ray, (t_plane*)l_objs->obj);
		if (l_objs->obj->obj_type == SPHERE)
			tmp = sphere_intersect(ray, (t_sphere*)l_objs->obj);
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
	int		x;
	int		y;
	double	distance;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			//	recuperer le vecteur directeur camera > pixel;

			//	tester les objs pour verifier si l'un d'eux est sur la route du rayon;
			distance = check_intersect(&ray, scn->objects);

			//	si un objet a ete rencontre, tester les lumieres et differents effets;
			x++;
		}
		y++;
	}
	return (0);
}
