/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:48:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/06 06:03:34 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene		*parsing_scene(char *scene)
{
	char		*data;
	t_camera	*cam;
	int			brightness;

	if (!(cam = parsing_camera(scene)))
		exit_custom_error("rt", ":parsing_camera() failed");
	if (!(data = get_interval(&scene, "<brightness>", "</brightness>")))
		return (NULL);
	if (between(brightness = atod(data), 0, 100) == -1)
		exit_custom_error("rt", ":brightness must be between <0 - 100>");
	free(data);
	return (new_scene(cam, brightness));
}
