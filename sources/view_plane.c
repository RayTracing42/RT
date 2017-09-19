/*============================================================================*/
/*                                                                            */
/*        fichier :   view_plane.c                                            */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

void	view_plane_vector(int x, int y, t_view_plane *vp, t_vector *cam_pixel)
{
	cam_pixel->x = vp->up_left.x + (vp->right.x * x) - (vp->up.x * y);
	cam_pixel->y = vp->up_left.y + (vp->right.y * x) - (vp->up.y * y);
	cam_pixel->z = vp->up_left.z + (vp->right.z * x) - (vp->up.z * y);
}

void	view_plane_rotation(t_view_plane *vp, double x, double y, double z)
{
	vp->front = matrice_rotation_x(&vp->front, x);
	vp->front = matrice_rotation_y(&vp->front, y);
	vp->front = matrice_rotation_z(&vp->front, z);
	vp->up = matrice_rotation_x(&vp->up, x);
	vp->up = matrice_rotation_y(&vp->up, y);
	vp->up = matrice_rotation_z(&vp->up, z);
	vp->right = matrice_rotation_x(&vp->right, x);
	vp->right = matrice_rotation_y(&vp->right, y);
	vp->right = matrice_rotation_z(&vp->right, z);
}

int		view_plane(t_camera *cam, t_view_plane *vp)
{
	double	dist_cam_vp;

	vp->fov = 70;
	vp->front = vector(1, 0, 0);
	vp->up = vector(0, 1, 0);
	vp->right = vector(0, 0 , 1);
	dist_cam_vp = (WIN_WIDTH / 2) / tan(vp->fov * M_PI / 180);
	vp->size = vector(dist_cam_vp, WIN_HEIGHT, WIN_WIDTH);
	view_plane_rotation(vp, (cam->angle_x * M_PI / 180),
		(cam->angle_y * M_PI / 180), (cam->angle_z * M_PI / 180));
	vp->up_left.x = cam->origin.x + ((vp->front.x * vp->size.x) +
		(vp->up.x * (vp->size.y / 2)) - (vp->right.x * (vp->size.z / 2)));
	vp->up_left.y = cam->origin.y + ((vp->front.y * vp->size.x) +
		(vp->up.y * (vp->size.y / 2)) - (vp->right.y * (vp->size.z / 2)));
	vp->up_left.z = cam->origin.z + ((vp->front.z * vp->size.x) +
		(vp->up.z * (vp->size.y / 2)) - (vp->right.z * (vp->size.z / 2)));
	return (0);
}
