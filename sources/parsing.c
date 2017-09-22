/*============================================================================*/
/*                                                                            */
/*        fichier :   parsing.c                                               */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

int		parsing_camera(t_camera *cam)
{
	/*
	**	Donnees pour faire des tests.
	*/
	if (!(cam->vp = (t_view_plane *)ft_memalloc(sizeof(t_view_plane))))
		return (-1);
	cam->origin = dot(0, 0, 0);
	cam->angle_x = 0;
	cam->angle_y = 0;
	cam->angle_z = 0;
	cam->vp->front = vector(1, 0, 0);
	cam->vp->up = vector(0, 1, 0);
	cam->vp->right = vector(0, 0, 1);
	cam->vp->fov = 70;
	return (0);
}
/*
int		parsing_objects(t_list_objs *l_objs)
{
	l_objs = NULL;
	return (0);
}

int		parsing_lights(t_list_lights *l_lights)
{
	l_lights = NULL;
	return (0);
}
*/
int		parsing(t_scene *scn, int argc, char **argv)
{
	if (argc && argv)
	{
		if (!(scn->cam = (t_camera *)ft_memalloc(sizeof(t_camera))))
			return (-1);
		if (parsing_camera(scn->cam) == -1)
			return (-1);
		scn->objects = NULL;
		scn->lights = NULL;
//		parsing_objects(scn->objects);
//		parsing_lights(scn->lights);
	}
	return (0);
}
