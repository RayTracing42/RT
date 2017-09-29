/*============================================================================*/
/*                                                                            */
/*        fichier :   shadows.c                                               */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

int		check_objs_on_ray(t_ray *light_ray, t_list_objs *l_objs, t_light *light)
{
	double	tmp;

	if (!light->is_in_light(light, light_ray->equ.vd))
		return (1);
	while (l_objs != NULL)
	{
		tmp = l_objs->obj->intersect(light_ray, l_objs->obj);
		if (tmp > 0 && tmp < 1)
			return (1);
		l_objs = l_objs->next;
	}
	return (0);
}

/*
t_ray	define_light_ray(t_dot inter, t_light *light)
{
	t_ray	ray;

	ray.equ.vc = vector(inter.x, inter.y, inter.z);
	// /!\ ATTENTION ; le resultat pour ORB et SPOT ne sont pas norme tandis que PARALLEL l'est si sa variable direction l'est.
	if (light->type == ORB)
		ray.equ.vd = define_vector_orb(inter, (t_orb_light*)light);
	if (light->type == SPOT)
		ray.equ.vd = define_vector_spot(inter, (t_spotlight*)light);
	if (light->type == PARALLEL)
		ray.equ.vd = define_vector_parallel((t_parallel_light*)light);
	return (ray);
}
*/

int		shadows(t_ray *ray, t_scene *scn)
{
	t_list_lights	*tmp;
	t_ray			light_ray;

	tmp = scn->lights;
	while (tmp != NULL)
	{
		//light_ray = define_light_ray(ray->inter, scn->lights->light);
		light_ray.equ.vd = tmp->light->get_ray_vect(&ray->inter, tmp->light);
		light_ray.equ.vc = *(t_vector*)&ray->inter;
		light_ray.color = ray->color;
		light_ray.normal = ray->normal;
		if (check_objs_on_ray(&light_ray, scn->objects, tmp->light))
			ray->color = (SDL_Color){0, 0, 0, 255};
		else
			ray->color = get_shade_col(&light_ray, scn);
		tmp = tmp->next;
	}
	return (0);
}
