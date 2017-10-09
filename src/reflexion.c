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
	t_ray		reflected_ray;

	if (ray->obj->obj_light.reflection_amount != 0)
	{
		reflected_ray = *ray;
		reflected_ray.equ.vc = vector(ray->inter.x, ray->inter.y, ray->inter.z);
		get_reflected_vect(&reflected_ray.equ.vd, &ray->normal);
	
		reflected_ray.color = effects(&reflected_ray, scn);
	}
	return (reflected_ray.color);
}
