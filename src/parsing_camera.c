/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:28:43 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/22 15:17:47 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera	*parsing_camera(char *scene)
{
	char		*data[5];
	t_dot		angle;
	t_dot		origin;
	t_camera	*cam;

	if (!(data[0] = get_interval(scene, "<camera>", "</camera>"))
		|| !(data[1] = get_interval(data[0], "<origin>", "</origin>"))
		|| !(data[2] = get_interval(data[0], "<angle>", "</angle>"))
		|| !(data[3] = get_interval(data[0], "<fov>", "</fov>"))
		|| !(data[4] = get_interval(data[0], "<dof>", "</dof>"))
		|| (parsing_dot(data[1], &origin) == -1)
		|| (parsing_dot(data[2], &angle) == -1))
		return (NULL);
	cam = new_camera(origin, angle, fabs(atod(data[3])), fabs(atod(data[4])));
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	free(data[4]);
	return (cam);
}
