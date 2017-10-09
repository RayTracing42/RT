/*============================================================================*/
/*                                                                            */
/*        fichier :   reflexion.c                                             */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

SDL_Color	reflect(t_ray *ray, t_scene *scn)
{
	t_vector	dir;

	if (ray->obj->obj_light.reflection_amount != 0)
	{	dir = ray->equ.vd;
		get_reflected_vect(&dir, &ray->normal);
	
		ray->color = effects(ray, scn);
	}
	return (ray->color);
}
