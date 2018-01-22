/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:22:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/18 18:32:37 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	check_objs_on_ray(t_ray *light_ray, t_list_objs *l_objs,
	t_light *light)
{
	double	tmp;
	t_ray	tmp_ray;

	if (!light->is_in_light(light, light_ray))
		return (1);
	tmp_ray = *light_ray;
	tmp_ray.shad_opacity = 0;
	tmp = check_intersect(&tmp_ray, l_objs);
	light_ray->shad_opacity = tmp_ray.shad_opacity;
	if (gt(tmp, 0) && lt(tmp, 1))
		return (1);
	return (0);
}

SDL_Color	add_colors(SDL_Color dst, SDL_Color src)
{
	SDL_Color res;

	res.r = (dst.r + src.r) <= 255 ? dst.r + src.r : 255;
	res.g = (dst.g + src.g) <= 255 ? dst.g + src.g : 255;
	res.b = (dst.b + src.b) <= 255 ? dst.b + src.b : 255;
	return (res);
}

static SDL_Color	div_colors(SDL_Color src, t_scene *scn)
{
	SDL_Color dst;

	dst.r = src.r * scn->brightness;
	dst.g = src.g * scn->brightness;
	dst.b = src.b * scn->brightness;
	return (dst);
}

void	opacify_color(SDL_Color *color, double opacity)
{
	opacity = 1 - ft_dmin(opacity, 1);
	color->r *= opacity;
	color->g *= opacity;
	color->b *= opacity;
}

SDL_Color	shadows(t_ray *ray, t_scene *scn)
{
	t_list_lights	*tmp;
	t_ray			light_ray;
	SDL_Color		multi_lights;

	multi_lights = div_colors(ray->color, scn);
	tmp = scn->lights;
	while (tmp != NULL)
	{
		light_ray.equ.vd = tmp->light->get_ray_vect(&ray->inter, tmp->light);
		light_ray.equ.vc = *(t_vector*)&ray->inter;
		light_ray.color = ray->color;
		if (check_objs_on_ray(&light_ray, scn->objects, tmp->light))
			opacify_color(&light_ray.color, light_ray.shad_opacity);
		light_ray.normal = ray->normal;
		light_ray.light = tmp->light;
		multi_lights = add_colors(multi_lights,
									add_colors(get_shade_col(&light_ray),
										get_specular_col(ray, &light_ray)));
		tmp = tmp->next;
	}
	return (multi_lights);
}
