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
	t_ray	tmp_ray;

	if (!light->is_in_light(light, light_ray))
		return (1);
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(light_ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && lt(tmp, 1))
		{
			if (is_in_limits(light_ray, &tmp_ray, l_objs->obj))
				return (1);
			else
			{
				tmp_ray = second_intersect(light_ray, l_objs->obj, &tmp);
				if (gt(tmp, 0) && lt(tmp, 1))
					if (is_in_limits(light_ray, &tmp_ray, l_objs->obj))
						return (1);
			}
		}
		l_objs = l_objs->next;
	}
	return (0);
}

SDL_Color	add_colors(SDL_Color dst, SDL_Color src)
{
	SDL_Color res;

	if ((dst.r + src.r) < 255)
		res.r = dst.r + src.r;
	else
		res.r = 255;
	if ((dst.g + src.g) < 255)
		res.g = dst.g + src.g;
	else
		res.g = 255;
	if ((dst.b + src.b) < 255)
		res.b = dst.b + src.b;
	else
		res.b = 255;
	return (res);
}

SDL_Color	div_colors(SDL_Color dst, t_scene *scn)
{
	SDL_Color res;

	res.r = dst.r * scn->brightness;
	res.g = dst.g * scn->brightness;
	res.b = dst.b * scn->brightness;
	return (res);
}

SDL_Color	shadows(t_ray *ray, t_scene *scn)
{
	t_list_lights	*tmp;
	t_ray			light_ray;
	SDL_Color		multi_lights;

	multi_lights = (SDL_Color){0, 0, 0, 255};
	tmp = scn->lights;
	while (tmp != NULL)
	{
		light_ray.equ.vd = tmp->light->get_ray_vect(&ray->inter, tmp->light);
		light_ray.equ.vc = *(t_vector*)&ray->inter;
		light_ray.color = ray->color;
		if (!(check_objs_on_ray(&light_ray, scn->objects, tmp->light)))
		{
			light_ray.normal = ray->normal;
			light_ray.light = tmp->light;
			multi_lights = add_colors(add_colors(multi_lights,
												get_shade_col(&light_ray)),
									get_specular_col(ray, &light_ray));
		}
		tmp = tmp->next;
	}
	return (div_colors(multi_lights, scn));
}
