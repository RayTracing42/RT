/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/21 13:12:56 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/22 15:21:52 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_camera	*new_camera(const t_dot origin, const t_dot angle, double field_of_view, double depth_of_field)
{
	t_camera	*cam;
	if (!(cam = malloc(sizeof(t_camera))))
		exit_error("rt", "malloc");
	cam->origin = origin;
	cam->angle = angle;
	cam->focal = WIN_WIDTH / (2 * tan((field_of_view * M_PI / 180) / 2.0f));
	cam->depth = depth_of_field;
	if (!(cam->vp = (t_view_plane *)ft_memalloc(sizeof(t_view_plane))))
		exit_error("rt", "malloc");
	cam->vp->front = vector(1, 0, 0);
	cam->vp->up = vector(0, 1, 0);
	cam->vp->right = vector(0, 0, 1);
	return (cam);
}

void		delete_camera(t_camera *cam)
{
	free(cam->vp);
	free(cam);
}
