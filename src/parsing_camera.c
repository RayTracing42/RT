/*============================================================================*/
/*                                                                            */
/*        fichier :   parsing_camera.c                                        */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

t_camera	*parsing_camera(char *scene)
{
	char		*data[4];
	t_dot		angle;
	t_dot		origin;
	double		focal;

	if (!(data[0] = get_interval(scene, "<camera>", "</camera>"))
		|| !(data[1] = get_interval(data[0], "<origin>", "</origin>"))
		|| !(data[2] = get_interval(data[0], "<angle>", "</angle>"))
		|| !(data[3] = get_interval(data[0], "<focal>", "</focal>"))
		|| (parsing_dot(data[1], &origin) == -1)
		|| (parsing_dot(data[2], &angle) == -1))
		return (NULL);
	focal = atoi(data[3]);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	free(data[3]);
	return (new_camera(focal, origin, angle.x, angle.y, angle.z));
}
