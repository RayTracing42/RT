/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_objects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:25:52 by fcecilie          #+#    #+#             */
/*   Updated: 2017/11/26 15:27:48 by fcecilie         ###   ########.fr       */
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
		|| !(data[2] = get_interval(object, "<physic>", "</physic>"))
		|| !(data[3] = get_interval(object, "<normal>", "</normal>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1)
		|| (parsing_physic(data[2], &args) == -1)
		|| (parsing_vector(data[3], &normal) == -1))
		return (NULL);
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
		|| !(data[2] = get_interval(object, "<physic>", "</physic>"))
		|| !(data[3] = get_interval(object, "<radius>", "</radius>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1)
		|| (parsing_physic(data[2], &args) == -1))
		return (NULL);
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
		|| !(data[2] = get_interval(object, "<physic>", "</physic>"))
		|| !(data[3] = get_interval(object, "<radius>", "</radius>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1)
		|| (parsing_physic(data[2], &args) == -1))
		return (NULL);
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
		|| !(data[2] = get_interval(object, "<physic>", "</physic>"))
		|| !(data[3] = get_interval(object, "<angle>", "</angle>"))
		|| (parsing_dot(data[0], &args.orig) == -1)
		|| (parsing_color(data[1], &args.col) == -1)
		|| (parsing_physic(data[2], &args) == -1))
		return (NULL);
	angle = atod(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_cone(args, angle));
}

int			parsing_object(char *scene, t_scene *scn)
{
	char		*data[2];
	t_object	*obj;

	while ((data[0] = get_interval(scene, "<object>", "</object>")))
	{
		obj = NULL;
		if (!(data[1] = get_interval(data[0], "<type>", "</type>")))
			return (-1);
		if (!(ft_strcmp(data[1], "sphere")) || !(ft_strcmp(data[1], "SPHERE")))
			obj = (t_object *)parsing_sphere(data[0]);
		else if (!(ft_strcmp(data[1], "plane"))
			|| !(ft_strcmp(data[1], "PLANE")))
			obj = (t_object *)parsing_plane(data[0]);
		else if (!(ft_strcmp(data[1], "cylinder"))
			|| !(ft_strcmp(data[1], "CYLINDER")))
			obj = (t_object *)parsing_cylinder(data[0]);
		else if (!(ft_strcmp(data[1], "cone")) || !(ft_strcmp(data[1], "CONE")))
			obj = (t_object *)parsing_cone(data[0]);
		else
			return (-1);
		if (!obj || (parsing_transformations(obj, data[0]) == -1))
			return (-1);
		parsing_limit(obj, data[0]);
		scene = ft_strstr(scene, "</object>") + ft_strlen("</object>");
		free(data[1]);
		free(data[0]);
		scene_add_object(obj, scn);
	}
	return (0);
}
