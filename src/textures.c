/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/11 11:43:21 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

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

void	spherical_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = 1 + (atan2(i.x,  i.z) / (M_PI));
	*u = *u * obj->texture->w * obj->txt_streching * 3;
	*v = 0.5 - (asin(i.y) / M_PI);
	*v = *v * obj->texture->h * obj->txt_streching * 3;
}

void	cylindrical_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = 1 + (atan2(i.x,  i.z) / (M_PI));
	*u = *u * obj->texture->w * obj->txt_streching;
	i.y /= sqrt(i.x * i.x + i.z * i.z);
	*v = mod(i.y * obj->texture->h * (obj->txt_streching / M_PI), obj->texture->h);
}

void	planar_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = mod(i.z * obj->texture->w * obj->txt_streching, obj->texture->w);
	*v = mod(i.y * obj->texture->h * obj->txt_streching, obj->texture->h);
}

SDL_Color getTextColor(t_parequation e, double t, t_object *obj)
{
	t_dot pt;
	t_dot vct;
	Uint32 color;
	double u;
	double v;
	SDL_Color	ret;

	pt.x = e.vc.x + e.vd.x * t;
	pt.y = e.vc.y + e.vd.y * t;
	pt.z = e.vc.z + e.vd.z * t;

	vct.x = pt.x - obj->origin.x;
	vct.y = pt.y - obj->origin.y;
	vct.z = pt.z - obj->origin.z;
	vct = norma(vct);
	planar_mapping(vct, &u, &v, obj);

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

	color = GetPixel32(obj->texture, mod(u, obj->texture->w), mod(v, obj->texture->h));
	//color = getpixel(obj->texture, (int)u % obj->texture->w, (int)v %  obj->texture->h);
	ret.a = 255;
	SDL_GetRGB(color, obj->texture->format, &ret.r, &ret.g, &ret.b);
	return (ret);
	//return (get_sdlcolor(color));
}
