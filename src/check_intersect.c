/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/10 13:16:28 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

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

Uint32 GetPixel32(SDL_Surface *image, int i, int j)
{
	if (i < 0 || i > image-> w - 1 || j < 0 || j > image-> h - 1)
		return 0;
	return (((Uint32*)(image->pixels))[j * (image->pitch / 4) + i]);
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int		bpp;
	Uint8	*p;

	bpp = surface->format->BytesPerPixel;
	p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
	if (bpp == 1)
		return (*p);
	else if (bpp == 2)
		return (*(Uint16 *)p);
	else if (bpp == 3)
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return (p[0] << 16 | p[1] << 8 | p[2]);
		else
			return (p[0] | p[1] << 8 | p[2] << 16);
	else if (bpp == 4)
		return (*(Uint32 *)p);
	return (0);
}

SDL_Color        get_sdlcolor(Uint32 i)
{
    SDL_Color    z;

    z.r = (i & 0xff0000) / 65536;
  	z.g = (i & 0x00ff00) / 256;
 	z.b = (i & 0x0000ff);
    z.a = 255;
    return (z);
}

double	do_dist(t_dot a)
{
	return (sqrt(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_dot	norma(t_dot a)
{
	double	dist;

	dist = do_dist(a);
	a.x = a.x / dist;
	a.y = a.y / dist;
	a.z = a.z / dist;
	return (a);
}

SDL_Color getTextColor(t_parequation e, double t, t_object *obj)
{
	t_dot pt;
	t_dot vct;
	Uint32 color;
	float u;
	float v;
	SDL_Color	ret;

	pt.x = e.vc.x + e.vd.x * t;
	pt.y = e.vc.y + e.vd.y * t;
	pt.z = e.vc.z + e.vd.z * t;

	vct.x = pt.x - obj->origin.x;
	vct.y = pt.y - obj->origin.y;
	vct.z = pt.z - obj->origin.z;
	vct = norma(vct);
	u = 0.5 + (atan2(vct.z,  vct.x) / (2 * M_PI));
	u = u * obj->texture->w * 15;
	v = 0.5 - (asin(vct.y) / M_PI);
	v = v * obj->texture->h * 15;

	/*while (u < 0)
		u = u + obj->texture->w;
	while (v < 0)
		v = v + obj->texture->h;
	while (u > obj->texture->w)
		u = u - obj->texture->w;
	while (v > obj->texture->h)
		v = v - obj->texture->h;*/
	// if (u > 0 && u < 1)
	// {
	// 	printf("%f, %f\n", u, v);
	// 	printf("%d, %d\n", obj->texture->w, obj->texture->h);
	// }
	// while (pt.x < 0)
	// 	pt.x = pt.x + obj->texture->w;
	// pt.x = (int)pt.x % (int)obj->texture->w;
	// while (pt.y < 0)
	// 	pt.y = pt.y + obj->texture->h;
	// pt.y = (int)pt.y % (int)obj->texture->h;
	// color = GetPixel32(obj->texture, pt.x, pt.y);

	color = GetPixel32(obj->texture, (int)u % obj->texture->w, (int)v %  obj->texture->h);
	//color = getpixel(obj->texture, (int)u % obj->texture->w, (int)v %  obj->texture->h);
	ret.a = 255;
	SDL_GetRGB(color, obj->texture->format, &ret.r, &ret.g, &ret.b);
	return (ret);
	//return (get_sdlcolor(color));
}

t_ray	first_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;
	t_parequation e;

	tmp_ray = *ray;
	e = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, e, obj, 1);
	tmp_ray.normal = obj->get_normal(&tmp_ray.inter, obj);
	if (obj->texture == NULL)
		tmp_ray.color = obj->color;
	else
		tmp_ray.color = getTextColor(e, *tmp, obj);
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
