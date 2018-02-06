/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:48:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/03 14:15:09 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene		*parsing_scene(char *scene)
{
	char		*data;
	t_camera	cam;
	int			brightness;

	if (parsing_camera(scene, &cam))
		exit_custom_error("rt", ":parsing_camera() failed");
	if (!(data = get_interval(scene, "<brightness>", "</brightness>")))
		return (NULL);
	if (between(brightness = atod(data), 0, 100) == -1)
		exit_custom_error("rt", ":brightness must be between <0 - 100>");
	free(data);
	return (new_scene(cam, brightness));
}
