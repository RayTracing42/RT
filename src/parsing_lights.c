/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:30:32 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/05 03:29:05 by fcecilie         ###   ########.fr       */
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

t_light				*parsing_light2(char *light, char *light_type)
{
	t_light		*lux;

	lux = NULL;
	if (!(ft_strcmp(light_type, "orb")))
		lux = (t_light *)parsing_orb_light(light);
	else if (!(ft_strcmp(light_type, "parallel")))
		lux = (t_light *)parsing_parallel_light(light);
	else if (!(ft_strcmp(light_type, "spot")))
		lux = (t_light *)parsing_spotlight(light);
	return (lux);
}

t_list_lights		*parsing_light(char *scene)
{
	char			*data[2];
	t_light			*lux;
	t_list_lights	*l;

	l = NULL;
	while ((data[0] = get_interval(scene, "<light>", "</light>")))
	{
		if (!(data[1] = get_interval(data[0], "<type>", "</type>")))
			return (NULL);
		if (!(lux = parsing_light2(data[0], data[1])))
			return (NULL);
		scene = ft_strstr(scene, "<light>") + ft_strlen("<light></light>") +
			ft_strlen(data[0]);
		free(data[1]);
		free(data[0]);
		new_cell_light(&l, lux);
	}
	return (l);
}
