/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/11 12:38:25 by shiro            ###   ########.fr       */
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

void	spherical_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = 1 + (atan2(i.x,  i.z) / (M_PI));
	*u = *u * obj->txt_data.texture->w * obj->txt_data.txt_streching * 3;
	*v = 0.5 - (asin(i.y) / M_PI);
	*v = *v * obj->txt_data.texture->h * obj->txt_data.txt_streching * 3;
}

void	cylindrical_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = 1 + (atan2(i.x,  i.z) / (M_PI));
	*u = *u * obj->txt_data.texture->w * obj->txt_data.txt_streching;
	i.y /= sqrt(i.x * i.x + i.z * i.z);
	*v = mod(i.y * obj->txt_data.texture->h * (obj->txt_data.txt_streching / M_PI), obj->txt_data.texture->h);
}

void	planar_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = mod(i.z * obj->txt_data.texture->w * obj->txt_data.txt_streching, obj->txt_data.texture->w);
	*v = mod(i.y * obj->txt_data.texture->h * obj->txt_data.txt_streching, obj->txt_data.texture->h);
}

SDL_Color getTextColor(t_parequation e, double t, t_object *obj)
{
	t_dot pt;
	Uint32 color;
	double u;
	double v;
	SDL_Color	ret;

	pt = equation_get_dot(&e, t);
	pt.x -= obj->origin.x;
	pt.y -= obj->origin.y;
	pt.z -= obj->origin.z;
	vect_normalize((t_vector*)&pt);
	obj->txt_data.texture_mapping(pt, &u, &v, obj);
	color = GetPixel32(obj->txt_data.texture, mod(u, obj->txt_data.texture->w), mod(v, obj->txt_data.texture->h));
	//color = getpixel(obj->texture, (int)u % obj->texture->w, (int)v %  obj->texture->h);
	ret.a = 255;
	SDL_GetRGB(color, obj->txt_data.texture->format, &ret.r, &ret.g, &ret.b);
	return (ret);
}
