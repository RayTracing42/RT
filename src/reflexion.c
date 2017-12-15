/*============================================================================*/
/*                                                                            */
/*        fichier :   reflexion.c                                             */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

t_vector	get_reflected_vect(t_vector *dir, const t_vector *norm)
{
	double	cos_theta1;

	cos_theta1 = vect_dot_product(norm, &(t_vector){-dir->x, -dir->y, -dir->z});
	return ((t_vector){dir->x + 2 * cos_theta1 * norm->x,
						dir->y + 2 * cos_theta1 * norm->y,
						dir->z + 2 * cos_theta1 * norm->z});
}

void		get_reflected_col(t_ray *ray, t_object *src,
				SDL_Color reflected_obj_col)
{
	ray->color.r = (ray->color.r * (1 - src->obj_light.reflection_amount)) +
			(reflected_obj_col.r * src->obj_light.reflection_amount);
	ray->color.g = (ray->color.g * (1 - src->obj_light.reflection_amount)) +
			(reflected_obj_col.g * src->obj_light.reflection_amount);
	ray->color.b = (ray->color.b * (1 - src->obj_light.reflection_amount)) +
			(reflected_obj_col.b * src->obj_light.reflection_amount);
}

SDL_Color	reflect(t_ray *ray, t_scene *scn)
{
	t_ray		reflected_ray;
	reflected_ray = *ray;
	if (ray->obj->obj_light.reflection_amount != 0 && ray->nb_intersect == 2)
	{
		if (ray->limit < 0.1)
			return ((SDL_Color){0, 0, 0, 255});
		reflected_ray.limit = reflected_ray.limit - (1 - ray->obj->obj_light.reflection_amount) / 100;
		reflected_ray.tree = add_new_leaf(ray->tree, &ray->tree->reflected, ray->obj, ray->tree->lvl);
		printf("%p -> r : %p (%p)\n", ray->obj, ray->tree->reflected, ray->tree);
		reflected_ray.equ.vc = vector(ray->inter.x, ray->inter.y, ray->inter.z);
		reflected_ray.equ.vd = get_reflected_vect(&ray->equ.vd, &ray->normal);
		effects(&reflected_ray, scn);
		//remove_leaf(reflected_ray.tree);
	}
	return (reflected_ray.color);
}
