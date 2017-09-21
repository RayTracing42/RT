/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:12:56 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 20:13:42 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>
/*
void		init_cam_screen(t_camera *cam)
{
	t_dot		tmp;
	t_matrix	*transfo;
	int			i;
	int			j;

	transfo = create_identity(4);
	translation(&transfo, cam->crd.x, cam->crd.y, cam->crd.z);
	y_rotation(&transfo, cam->theta);
	x_rotation(&transfo, cam->phi);
	tmp.x = -WIN_WIDTH / 2;
	i = 0;
	while ((i += cam->resolution) < WIN_WIDTH)
	{
		tmp.x += cam->resolution;
		tmp.y = -WIN_HEIGHT / 2;
		j = 0;
		while ((j += cam->resolution) < WIN_HEIGHT)
		{
			tmp.y += cam->resolution;
			set_dot(&cam->screen[i][j], tmp.x, tmp.y, cam->f);
			mult_vect((t_vector*)&cam->screen[i][j], transfo,
						(t_vector*)&cam->screen[i][j]);
		}
	}
}*/

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
	//init_cam_screen(cam);
	return (cam);
}

void		delete_camera(t_camera *cam)
{
	free(cam);
}
