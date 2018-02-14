/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:22:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/14 16:41:05 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
**	t_dot pixel correspond au point sur le view_plane
**	t_dot diff corresppond au vecteur cam > pixel non normé
**	on divise donc diff par sa longueur afin d'obtenir le vecteur normé
*/

void	view_plane_vector(int x, int y, t_camera *cam, t_vector *vd)
{
	t_dot	pixel;

	pixel.x = cam->vp.up_left.x + (cam->vp.right.x * x) - (cam->vp.up.x * y);
	pixel.y = cam->vp.up_left.y + (cam->vp.right.y * x) - (cam->vp.up.y * y);
	pixel.z = cam->vp.up_left.z + (cam->vp.right.z * x) - (cam->vp.up.z * y);
	*vd = vector(pixel.x - cam->origin.x, pixel.y - cam->origin.y,
			pixel.z - cam->origin.z);
}

void	view_plane_rotation(t_view_plane *vp, double x, double y, double z)
{
	vp->front = vector_rotation_z(&vp->front, z);
	vp->front = vector_rotation_y(&vp->front, y);
	vp->front = vector_rotation_x(&vp->front, x);
	vp->up = vector_rotation_z(&vp->up, z);
	vp->up = vector_rotation_y(&vp->up, y);
	vp->up = vector_rotation_x(&vp->up, x);
	vp->right = vector_rotation_z(&vp->right, z);
	vp->right = vector_rotation_y(&vp->right, y);
	vp->right = vector_rotation_x(&vp->right, x);
}

void	view_plane(t_camera *cam)
{
	cam->vp.size = vector(cam->focal, WIN_HEIGHT, WIN_WIDTH);
	view_plane_rotation(&cam->vp, ft_to_rad(cam->angle.x),
						ft_to_rad(cam->angle.y), ft_to_rad(cam->angle.z));
	cam->vp.up_left.x = cam->origin.x + (cam->vp.front.x * cam->vp.size.x +
		cam->vp.up.x * cam->vp.size.y / 2 - cam->vp.right.x * cam->vp.size.z / 2);
	cam->vp.up_left.y = cam->origin.y + (cam->vp.front.y * cam->vp.size.x +
		cam->vp.up.y * cam->vp.size.y / 2 - cam->vp.right.y * cam->vp.size.z / 2);
	cam->vp.up_left.z = cam->origin.z + (cam->vp.front.z * cam->vp.size.x +
		cam->vp.up.z * cam->vp.size.y / 2 - cam->vp.right.z * cam->vp.size.z / 2);
}
