/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:22:51 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/15 16:45:51 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static SDL_Color	add_colors(SDL_Color dst, SDL_Color src)
{
	SDL_Color res;

	res.r = (dst.r + src.r) < 255 ? dst.r + src.r : 255;
	res.g = (dst.g + src.g) < 255 ? dst.g + src.g : 255;
	res.b = (dst.b + src.b) < 255 ? dst.b + src.b : 255;
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

static void	opacify_color(t_ray *light_ray, double *opacity)
{
	*opacity = 1 - ft_dmin(light_ray->shad_opacity, 1);
	light_ray->color.r *= *opacity;
	light_ray->color.g *= *opacity;
	light_ray->color.b *= *opacity;
}

static SDL_Color	color_mod(SDL_Color src1, SDL_Color src2)
{
	return ((SDL_Color){src1.r * src2.r / 255,
						src1.g * src2.g / 255,
						src1.b * src2.b / 255, 255});
}

SDL_Color			shadows(t_ray *ray, t_scene *scn)
{
	t_list_lights	*tmp;
	t_ray			light_ray;
	SDL_Color		multi_lights;
	double			opacity[2];

	multi_lights = div_colors(ray->color, scn);
	tmp = scn->lights;
	while (tmp != NULL)
	{
		light_ray.equ.vd = tmp->light->get_ray_vect(ray->inter, tmp->light);
		light_ray.equ.vc = *(t_vector*)&ray->inter;
		light_ray.color = ray->color;
		opacity[0] = 1;
		if (check_objs_on_ray(&light_ray, scn->objects, tmp->light, ray->i_intersect == 1 ? ray->obj : NULL))
			opacify_color(&light_ray, &opacity[0]);
		light_ray.normal = ray->normal;
		light_ray.light = tmp->light;
		multi_lights = add_colors(color_mod(multi_lights,
			light_ray.light->color), add_colors(get_specular_col(ray,
				&light_ray, opacity[0], opacity[1]),
				get_shade_col(&light_ray, opacity[0], &opacity[1])));
		tmp = tmp->next;
	}
	multi_lights.a = 255;
	return (multi_lights);
}
