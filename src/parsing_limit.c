/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_limit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:57:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/22 10:53:15 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parsing_global_limit(t_object *o, t_dot origin, t_vector normal,
			int status)
{
	t_plane			*p;
	t_trans_data	trans;

	p = new_plane((t_objs_comp){origin, o->color,
		o->obj_light.reflection_amount, o->obj_light.refraction_amount,
		o->obj_light.refractive_index, o->obj_light.shininess}, normal);
	p->status = status;
	p->lim_type = GLOBAL;
	p->orig_diff = (t_vector){origin.x - o->origin.x, origin.y - o->origin.y,
		origin.z - o->origin.z};
	trans = (t_trans_data){(t_dot){0, 0, 0}, (t_dot){0, 0, 0},
		(t_dot){1, 1, 1}};
	normalized_diff(p, &trans.trans);
	trans = (t_trans_data){(t_dot){0, 0, 0}, (t_dot){0, 0, 0},
		(t_dot){1, 1, 1}};
	set_all_matrix((t_object *)p, trans);
	if (!(o->limit))
		o->limit = new_cell_obj(NULL, (t_object *)p);
	else
		new_cell_obj(&o->limit, (t_object *)p);
}

void	parsing_local_limit(t_object *o, t_trans_data trans, t_dot origin,
			t_vector normal, int status)
{
	t_plane		*p;

	p = new_plane((t_objs_comp){o->origin, o->color,
		o->obj_light.reflection_amount, o->obj_light.refraction_amount,
		o->obj_light.refractive_index, o->obj_light.shininess}, normal);
	p->orig_diff = (t_vector){origin.x - o->origin.x, origin.y - o->origin.y,
		origin.z - o->origin.z};
	p->status = status;
	p->lim_type = LOCAL;
	normalized_diff(p, &trans.trans);
	set_all_matrix((t_object *)p, trans);
	if (!(o->limit))
		o->limit = new_cell_obj(NULL, (t_object *)p);
	else
		new_cell_obj(&o->limit, (t_object *)p);
}

void	global_loop(t_object *obj, char *limit)
{
	char		*data[4];
	t_dot		origin;
	t_vector	normal;
	int			status;

	while ((data[0] = get_interval(limit, "<global>", "</global>")))
	{
		if (!(data[1] = get_interval(data[0], "<origin>", "</origin>"))
			|| !(data[2] = get_interval(data[0], "<normal>", "</normal>"))
			|| !(data[3] = get_interval(data[0], "<status>", "</status>"))
			|| (parsing_dot(data[1], &origin) == -1)
			|| (parsing_vector(data[2], &normal) == -1)
			|| ((status = get_status(data[3])) == -1))
			exit_custom_error("rt", ":global_loop failed");
		parsing_global_limit(obj, origin, normal, status);
		limit = ft_strstr(limit, "</global>") + ft_strlen("</global>");
		free(data[0]);
		free(data[1]);
		free(data[2]);
		free(data[3]);
	}
}

void	local_loop(t_object *obj, char *limit, t_trans_data trans)
{
	char		*data[4];
	t_dot		origin;
	t_vector	normal;
	int			status;

	while ((data[0] = get_interval(limit, "<local>", "</local>")))
	{
		if (!(data[1] = get_interval(data[0], "<origin>", "</origin>"))
			|| !(data[2] = get_interval(data[0], "<normal>", "</normal>"))
			|| !(data[3] = get_interval(data[0], "<status>", "</status>"))
			|| (parsing_dot(data[1], &origin) == -1)
			|| (parsing_vector(data[2], &normal) == -1)
			|| ((status = get_status(data[3])) == -1))
			exit_custom_error("rt", ":local_loop failed");
		parsing_local_limit(obj, trans, origin, normal, status);
		limit = ft_strstr(limit, "</local>") + ft_strlen("</local>");
		free(data[0]);
		free(data[1]);
		free(data[2]);
		free(data[3]);
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
