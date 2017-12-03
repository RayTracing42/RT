/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_limit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:57:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/11/29 04:06:37 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	*parsing_value_limit(char *limit, char *start, char *stop)
{
	char	*data;
	double	*nb;

	if (!(data = get_interval(limit, start, stop)))
		nb = NULL;
	else
	{
		if (!(nb = ft_memalloc(sizeof(double *))))
			exit_error("rt", "malloc");
		else
			*nb = atod(data);
	}
	free(data);
	return (nb);
}

t_plane	*parsing_plane_limit(t_object *obj, t_vector normal, double *nb)
{
	t_plane 	*p;
	t_dot		origin;
	
	p = NULL;
	if (nb)
	{
		origin = (t_dot){0, 0, 0};
		if ((normal.x == 1) || (normal.x == -1))
			origin.x = *nb;
		else if ((normal.y == 1) || (normal.y == -1))
			origin.y = *nb;
		else if ((normal.z == 1) || (normal.z == -1))
			origin.z = *nb;

		p = new_plane((t_objs_comp){origin, obj->color,
			obj->obj_light.reflection_amount, obj->obj_light.refraction_amount,
			obj->obj_light.refractive_index, obj->obj_light.shininess}, normal);
	}
	return (p);
}

void	parsing_unit_limit(t_object *obj, char *lim, t_limit *l)
{
	if (!(l->nb = (double **)ft_memalloc(sizeof(double *) * 6)))
		exit_error("rt", "malloc");
	if (!(l->p = (t_plane **)ft_memalloc(sizeof(t_plane *) * 6)))
		exit_error("rt", "malloc");
	l->nb[0] = parsing_value_limit(lim, "<up_x>", "</up_x>");
	l->nb[1] = parsing_value_limit(lim, "<up_y>", "</up_y>");
	l->nb[2] = parsing_value_limit(lim, "<up_z>", "</up_z>");
	l->nb[3] = parsing_value_limit(lim, "<down_x>", "</down_x>");
	l->nb[4] = parsing_value_limit(lim, "<down_y>", "</down_y>");
	l->nb[5] = parsing_value_limit(lim, "<down_z>", "</down_z>");
	l->p[0] = parsing_plane_limit(obj, (t_vector){1, 0, 0}, l->nb[0]);
	l->p[1] = parsing_plane_limit(obj, (t_vector){0, 1, 0}, l->nb[1]);
	l->p[2] = parsing_plane_limit(obj, (t_vector){0, 0, 1}, l->nb[2]);
	l->p[3] = parsing_plane_limit(obj, (t_vector){-1, 0, 0}, l->nb[3]);
	l->p[4] = parsing_plane_limit(obj, (t_vector){0, -1, 0}, l->nb[4]);
	l->p[5] = parsing_plane_limit(obj, (t_vector){0, 0, -1}, l->nb[5]);
}

void	parsing_limit(t_object *obj, char *object)
{
	char	*data[3];

	data[0] = get_interval(object, "<limit>", "</limit>");
	data[1] = get_interval(data[0], "<local>", "</local>");
	data[2] = get_interval(data[0], "<global>", "</global>");
	parsing_unit_limit(obj, data[1], &obj->local_limit);
	parsing_unit_limit(obj, data[2], &obj->global_limit);
	free(data[0]);
	free(data[1]);
	free(data[2]);
}
