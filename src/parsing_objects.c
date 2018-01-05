/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:25:52 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/05 03:50:12 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_plane		*parsing_plane(char *object)
{
	char		*data[4];
	t_objs_comp args;
	t_vector	normal;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<color>", "</color>"))
		|| !(data[3] = get_interval(object, "<normal>", "</normal>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1)
		|| (parsing_vector(data[3], &normal) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_plane(args, normal));
}

t_sphere	*parsing_sphere(char *object)
{
	char		*data[4];
	t_objs_comp args;
	double		radius;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<color>", "</color>"))
		|| !(data[3] = get_interval(object, "<radius>", "</radius>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	radius = atod(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_sphere(args, radius));
}

t_cylinder	*parsing_cylinder(char *object)
{
	char		*data[4];
	t_objs_comp args;
	double		radius;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<color>", "</color>"))
		|| !(data[3] = get_interval(object, "<radius>", "</radius>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	radius = atod(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_cylinder(args, radius));
}

t_cone		*parsing_cone(char *object)
{
	char		*data[4];
	t_objs_comp args;
	double		angle;

	if (!(data[0] = get_interval(object, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(object, "<color>", "</color>"))
		|| !(data[3] = get_interval(object, "<angle>", "</angle>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1))
		return (NULL);
	data[2] = get_interval(object, "<physic>", "</physic>");
	parsing_physic(data[2], &args);
	angle = atod(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_cone(args, angle));
}

t_object	*parsing_object2(char *object, char *object_type)
{
	t_object *obj;

	obj = NULL;
	if (!(ft_strcmp(object_type, "sphere")))
		obj = (t_object *)parsing_sphere(object);
	else if (!(ft_strcmp(object_type, "plane")))
		obj = (t_object *)parsing_plane(object);
	else if (!(ft_strcmp(object_type, "cylinder")))
		obj = (t_object *)parsing_cylinder(object);
	else if (!(ft_strcmp(object_type, "cone")))
		obj = (t_object *)parsing_cone(object);
	return (obj);
}

t_list_objs	*parsing_object(char *scene)
{
	char			*data[2];
	t_object		*obj;
	t_list_objs		*l;

	l = NULL;
	while ((data[0] = get_interval(scene, "<object>", "</object>")))
	{
		if (!(data[1] = get_interval(data[0], "<type>", "</type>")))
			return (NULL);
		if (!(obj = parsing_object2(data[0], data[1])))
			return (NULL);
		parsing_transformations(obj, data[0]);
		parsing_limit(obj, data[0]);
		if (parsing_negative_obj(obj, data[0]) == -1)
			return (NULL);
		scene = ft_strstr(scene, "<object>") + ft_strlen("<object></object>") +
			ft_strlen(data[0]);
		free(data[1]);
		free(data[0]);
		new_cell_obj(&l, obj);
	}
	return (l);
}
