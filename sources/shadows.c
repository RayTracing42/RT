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
	double	distance_1;
	double	distance_2;
	double	tmp;
	t_dot	vc;

	vc = dot(light_ray->equ.vc.x, light_ray->equ.vc.y, light_ray->equ.vc.z);
	if (!light->is_in_light(light, light_ray->equ.vd))
		return (1);
	while (l_objs != NULL)
	{
		tmp = 0;
		tmp = l_objs->obj->intersect(light_ray, l_objs->obj);
		distance_1 = get_vect_lenght(&light_ray->equ.vd);
		distance_2 = get_dot_dist(&light_ray->inter, &vc);
		if (tmp > 0.00000000000000000000001 && distance_2 < distance_1)
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
	int				nb_lights;
	int				hidden_lights;

	tmp = scn->lights;
	nb_lights = 0;
	hidden_lights = 0;
	while (tmp != NULL)
	{
		//light_ray = define_light_ray(ray->inter, scn->lights->light);
		light_ray.equ.vd = tmp->light->get_ray_vect(&ray->inter, &tmp->light);
		*(t_dot*)&light_ray.equ.vc = ray->inter;
		light_ray.color = ray->color;
		light_ray.normal = ray->normal;
		if (check_objs_on_ray(&light_ray, scn->objects, scn->lights->light) == 1)
		{
			hidden_lights++;
			ray->color.r = 0;
			ray->color.g = 0;
			ray->color.b = 0;
		}
		else
			ray->color = get_shade_col(&light_ray, scn);
		nb_lights++;
		tmp = tmp->next;
	}
	return (0);
}
