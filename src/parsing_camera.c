/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_camera.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 15:28:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/22 11:01:43 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_camera	*parsing_camera(char *scene)
{
	char		*data[3];
	t_dot		angle;
	t_dot		origin;

	if (!(data[0] = get_interval(scene, "<camera>", "</camera>"))
		|| !(data[1] = get_interval(data[0], "<origin>", "</origin>"))
		|| !(data[2] = get_interval(data[0], "<angle>", "</angle>"))
		|| (parsing_dot(data[1], &origin) == -1)
		|| (parsing_dot(data[2], &angle) == -1))
		return (NULL);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	return (new_camera(origin, angle.x, angle.y, angle.z));
}
