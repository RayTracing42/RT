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

void	parsing_global_limit(t_object *o, char *limit)
{
	t_dot		origin;
	t_vector	normal;
	char		*data[2];
	t_plane		*p;

	if (!(data[0] = get_interval(limit, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(limit, "<normal>", "</normal>"))
		|| (parsing_dot(data[0], &origin) == -1)
		|| (parsing_vector(data[1], &normal) == -1))
		exit_custom_error("rt", ":parsing_global_limit failed");
	p = new_plane((t_objs_comp){origin, o->color, o->obj_light.reflection_amount,
			o->obj_light.refraction_amount, o->obj_light.refractive_index,
			o->obj_light.shininess}, normal);
	set_all_matrix((t_object *)p, (t_trans_data){(t_dot){0, 0, 0},
			(t_dot){0, 0, 0}, (t_dot){1, 1, 1}});
	free(data[0]);
	free(data[1]);
	if (!(o->global_limit))
		o->global_limit = new_cell_obj(NULL, (t_object *)p);
	else
		new_cell_obj(&o->global_limit, (t_object *)p);
}

void	parsing_local_limit(t_object *o, char *limit, t_trans_data trans)
{
	t_dot		origin;
	t_vector	normal;
	char		*data[2];
	t_plane		*p;

	if (!(data[0] = get_interval(limit, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(limit, "<normal>", "</normal>"))
		|| (parsing_dot(data[0], &origin) == -1)
		|| (parsing_vector(data[1], &normal) == -1))
		exit_custom_error("rt", ":parsing_local_limit failed");
	p = new_plane((t_objs_comp){o->origin, o->color, o->obj_light.reflection_amount,
			o->obj_light.refraction_amount, o->obj_light.refractive_index,
			o->obj_light.shininess}, normal);
	p->exceeding_limit.x = origin.x - o->origin.x;
	p->exceeding_limit.y = origin.y - o->origin.y;
	p->exceeding_limit.z = origin.z - o->origin.z;
	trans.trans.x += p->exceeding_limit.x;
	trans.trans.y += p->exceeding_limit.y;
	trans.trans.z += p->exceeding_limit.z;
//	printf("exceed : (%.2f, %.2f, %.2f)\n", p->exceeding_limit.x, p->exceeding_limit.y, p->exceeding_limit.z);
	set_all_matrix((t_object *)p, trans);
	free(data[0]);
	free(data[1]);
	if (!(o->local_limit))
		o->local_limit = new_cell_obj(NULL, (t_object *)p);
	else
		new_cell_obj(&o->local_limit, (t_object *)p);
}

void	global_loop(t_object *obj, char *limit)
{
	char	*data;

	while ((data = get_interval(limit, "<global>", "</global>")))
	{
		parsing_global_limit(obj, data);
		limit = ft_strstr(limit, "</global>") + ft_strlen("</global>");
		free(data);
	}
}

void	local_loop(t_object *obj, char *limit, t_trans_data trans)
{
	char	*data;

	while ((data = get_interval(limit, "<local>", "</local>")))
	{
		parsing_local_limit(obj, data, trans);
		limit = ft_strstr(limit, "</local>") + ft_strlen("</local>");
		free(data);
	}
}

void	parsing_limit(t_object *obj, char *object, t_trans_data trans)
{
	char	*data;

	if (!(data = get_interval(object, "<limit>", "</limit>")))
		return ;
	local_loop(obj, data, trans);
	global_loop(obj, data);
	free(data);
}
