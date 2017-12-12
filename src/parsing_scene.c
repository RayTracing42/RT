/*============================================================================*/
/*                                                                            */
/*        fichier :   parsing_scene.c                                         */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

t_scene		*parsing_scene(char *scene)
{
	char		*data;
	t_camera	*cam;
	int			brightness;
	
	if (!(cam = parsing_camera(scene)))
		exit_custom_error("rt", ":parsing_camera() failed");
	if (!(data = get_interval(scene, "<brightness>", "</brightness>")))
		return (NULL);
	brightness = atod(data);
	free(data);
	return (new_scene(cam, brightness));
}
