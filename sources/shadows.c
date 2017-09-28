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
	t_list_objs	*first;
	double	distance;

	distance = 0;
	first = l_objs;
	while (l_objs != NULL)
	{	
		distance = l_objs->obj->intersect(light_ray, l_objs->obj);
		if ((distance > 0) || (light->type == SPOT && light->is_in_light((t_spotlight *)light, light_ray->equ.vd) == 0))
			return (1);
		l_objs = l_objs->next;
	}
	l_objs = first;
	return (0);
}


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

int		shadows(t_ray *ray, t_scene *scn)
{
	t_list_lights	*first;
	t_ray			light_ray;
	int				nb_lights;
	int				hidden_lights;

	first = scn->lights;
	nb_lights = 0;
	hidden_lights = 0;
	while (scn->lights != NULL)
	{
		light_ray = define_light_ray(ray->inter, scn->lights->light);
		light_ray.color = ray->color;
		if (check_objs_on_ray(&light_ray, scn->objects, scn->lights->light) == 1)
		{
			hidden_lights++;
			ray->color.r = 0;
			ray->color.g = 0;
			ray->color.b = 0;
		}
	//	else
	//		ray->color = get_shade_col(&light_ray, scn);
		nb_lights++;
		scn->lights = scn->lights->next;
	}
	scn->lights = first;
	return (0);
}
