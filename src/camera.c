/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:12:56 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 20:40:41 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_camera	*new_camera(int fov, const t_dot origin,
						double angle_x, double angle_y, double angle_z)
{
	t_camera	*cam;

	if (!(cam = malloc(sizeof(t_camera))))
		exit_error("rtv1", "malloc");
	cam->origin = origin;
	cam->angle_x = angle_x;
	cam->angle_y = angle_y;
	cam->angle_z = angle_z;
	cam->focal = WIN_WIDTH / (2 * tan(ft_to_rad(fov) / 2.0f));
	return (cam);
}

void		delete_camera(t_camera *cam)
{
	free(cam);
}
