/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:12:56 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 20:19:32 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static void	init_cam_screen(t_camera *cam)
{
	t_dot		tmp;
	int			i;
	int			j;

	tmp.x = -WIN_WIDTH / 2;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		tmp.x++;
		tmp.y = -WIN_HEIGHT / 2;
		j = -1;
		while (++j < WIN_HEIGHT)
		{
			tmp.y++;
			cam->screen[i][j] = (t_dot){tmp.x, tmp.y, cam->focal};
		}
	}
}

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
	init_cam_screen(cam);
	return (cam);
}

void		delete_camera(t_camera *cam)
{
	free(cam);
}
