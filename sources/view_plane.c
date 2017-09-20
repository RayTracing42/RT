/*============================================================================*/
/*                                                                            */
/*        fichier :   view_plane.c                                            */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

/*
**	t_dot pixel correspond au point sur le view_plane
**	t_dot diff corresppond au vecteur cam > pixel non normé
**	on divise donc diff par sa longueur afin d'obtenir le vecteur normé
*/

void	view_plane_vector(int x, int y, t_camera *cam, t_vector *cam_pixel)
{
	t_dot	pixel;
	t_dot	diff;
	double	vector_distance;

	pixel.x = cam->vp->up_left.x + (cam->vp->right.x * x) - (cam->vp->up.x * y);
	pixel.y = cam->vp->up_left.y + (cam->vp->right.y * x) - (cam->vp->up.y * y);
	pixel.z = cam->vp->up_left.z + (cam->vp->right.z * x) - (cam->vp->up.z * y);
	diff.x = pixel.x - cam->origin.x;
	diff.y = pixel.y - cam->origin.y;
	diff.z = pixel.z - cam->origin.z;
	vector_distance = sqrt(pow(diff.x, 2) + pow(diff.y, 2) + pow(diff.z, 2));
	cam_pixel->x = diff.x / vector_distance;
	cam_pixel->y = diff.y / vector_distance;
	cam_pixel->z = diff.z / vector_distance;
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

	dist_cam_vp = (WIN_WIDTH / 2) / tan((vp->fov / 2) * M_PI / 180);
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
