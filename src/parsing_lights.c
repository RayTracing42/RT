/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:30:32 by fcecilie          #+#    #+#             */
/*   Updated: 2017/11/26 15:42:34 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_parallel_light	*parsing_parallel_light(char *light)
{
	char		*data[3];
	t_vector	direction;
	SDL_Color	color;
	double		power;

	if (!(data[0] = get_interval(light, "<direction>", "</direction>"))
		|| !(data[1] = get_interval(light, "<color>", "</color>"))
		|| !(data[2] = get_interval(light, "<power>", "</power>"))
		|| (parsing_vector(data[0], &direction) == -1)
		|| (parsing_color(data[1], &color) == -1))
		return (NULL);
	power = atod(data[2]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	return (new_parallel_light(direction, color, power));
}

t_spotlight			*parsing_spotlight(char *light)
{
	char		*data[5];
	t_light_crd	coords;
	SDL_Color	color;
	double		power;
	double		aperture;

	if (!(data[0] = get_interval(light, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(light, "<direction>", "</direction>"))
		|| !(data[2] = get_interval(light, "<color>", "</color>"))
		|| !(data[3] = get_interval(light, "<power>", "</power>"))
		|| !(data[4] = get_interval(light, "<aperture>", "</aperture>"))
		|| (parsing_dot(data[0], &coords.orig) == -1)
		|| (parsing_vector(data[1], &coords.direction) == -1)
		|| (parsing_color(data[2], &color) == -1))
		return (NULL);
	power = atod(data[3]);
	aperture = atod(data[4]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	free(data[4]);
	return (new_spotlight(coords, color, aperture, power));
}

t_orb_light			*parsing_orb_light(char *light)
{
	char		*data[3];
	t_dot		origin;
	SDL_Color	color;
	double		power;

	if (!(data[0] = get_interval(light, "<origin>", "</origin>"))
		|| !(data[1] = get_interval(light, "<color>", "</color>"))
		|| !(data[2] = get_interval(light, "<power>", "</power>"))
		|| (parsing_dot(data[0], &origin) == -1)
		|| (parsing_color(data[1], &color) == -1))
		return (NULL);
	power = atod(data[2]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	return (new_orb_light(origin, color, power));
}

int					parsing_ambient_light(char *scene, t_scene *scn)
{
	t_light	*lux;
	char	*data;

	if (!(data = get_interval(scene, "<ambient_light>", "</ambient_light>")))
		return (-1);
	if (!(lux = (t_light *)parsing_parallel_light(data)))
		return (-1);
	free(data);
	scene_add_light(lux, scn);
	return (0);
}

int					parsing_light(char *scene, t_scene *scn)
{
	char		*data[2];
	t_light		*lux;

	while ((data[0] = get_interval(scene, "<light>", "</light>")))
	{
		lux = NULL;
		if (!(data[1] = get_interval(data[0], "<type>", "</type>")))
			return (-1);
		if (!(ft_strcmp(data[1], "orb")) || !(ft_strcmp(data[1], "ORB")))
			lux = (t_light *)parsing_orb_light(data[0]);
		else if (!(ft_strcmp(data[1], "parallel"))
			|| !(ft_strcmp(data[1], "PARALLEL")))
			lux = (t_light *)parsing_parallel_light(data[0]);
		else if (!(ft_strcmp(data[1], "spot")) || !(ft_strcmp(data[1], "SPOT")))
			lux = (t_light *)parsing_spotlight(data[0]);
		else
			return (-1);
		if (!lux)
			return (-1);
		scene = ft_strstr(scene, "</light>") + ft_strlen("</light>");
		free(data[1]);
		free(data[0]);
		scene_add_light(lux, scn);
	}
	return (0);
}
