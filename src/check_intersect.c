/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/30 16:21:22 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		dist;
	double		tmp;
	t_ray		tmp_ray;

	dist = 0;
	tmp_ray.shad_opacity = 0;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			transform_inter(&tmp_ray, tmp_ray.obj);
			if (is_in_limit(&tmp_ray, l_objs->obj))
			{
				dist = tmp;
				*ray = tmp_ray;
			}
			else
				check_limit_intersect(ray, l_objs->obj, &dist);
		}
		l_objs = l_objs->next;
	}
	return (dist);
}

Uint32 GetPixel32(SDL_Surface* image,int i,int j)
{
    if (i<0 || i>image->w-1 || j<0 || j>image->h-1)
        return 0;
    return ((Uint32*)(image->pixels))[j*(image->pitch/4)+i];
}

SDL_Color        get_sdlcolor(int i)
{
    SDL_Color    z;

    z.r = (i & 0xff0000) / 65536;
  	z.g = (i & 0x00ff00) / 256;
 	z.b = (i & 0x0000ff);
    z.a = 255;
    return (z);
}

SDL_Color getTextColor(t_parequation e, double t, t_object *obj)
{
	t_dot pt;
	Uint32 color;

	pt.x = e.vc.x + e.vd.x * t;
	pt.y = e.vc.y + e.vd.y * t;
	pt.z = e.vc.z + e.vd.z * t;

	while (pt.x < 0)
		pt.x = pt.x + obj->texture->w;
	pt.x = (int)pt.x % (int)obj->texture->w;
	while (pt.y < 0)
		pt.y = pt.y + obj->texture->h;
	pt.y = (int)pt.y % (int)obj->texture->h;
	color = GetPixel32(obj->texture, pt.x, pt.y);
	return (get_sdlcolor((int)color));
}

t_ray	first_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;
	t_parequation e;

	tmp_ray = *ray;
	e = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, e, obj, 1);
	tmp_ray.normal = obj->get_normal(&tmp_ray.inter, obj);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}

t_ray	second_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 2);
	tmp_ray.normal = obj->get_normal(&tmp_ray.inter, obj);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	return (tmp_ray);
}
