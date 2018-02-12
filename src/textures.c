/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/12 13:41:48 by shiro            ###   ########.fr       */
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

void	spherical_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = 1 + (atan2(i.x,  i.z) / (M_PI));
	*u *= obj->material.texture->w * obj->material.txt_streching;
	*v = 0.5 - (asin(i.y) / M_PI);
	*v *= obj->material.texture->h * obj->material.txt_streching;
}

void	cylindrical_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = 1 + (atan2(i.x,  i.z) / (M_PI));
	*u *= obj->material.texture->w * obj->material.txt_streching;
	i.y /= sqrt(i.x * i.x + i.z * i.z);
	*v = mod(i.y * obj->material.texture->h * (obj->material.txt_streching / M_PI), obj->material.texture->h);
}

void	planar_mapping(t_dot i, double *u, double *v, t_object *obj)
{
	*u = mod(i.z * obj->material.texture->w * obj->material.txt_streching / M_PI, obj->material.texture->w);
	*v = mod(i.y * obj->material.texture->h * obj->material.txt_streching / M_PI, obj->material.texture->h);
}

SDL_Color getTextColor(t_parequation e, double t, t_object *obj)
{
	t_dot	pt;
	t_dot	textel;
	Uint32 color;
	SDL_Color	ret;

	pt = equation_get_dot(&e, t);
	pt.x -= obj->origin.x;
	pt.y -= obj->origin.y;
	pt.z -= obj->origin.z;
	vect_normalize((t_vector*)&pt);
	obj->material.texture_mapping(pt, &textel.x, &textel.y, obj);
	color = GetPixel32(obj->material.texture, mod(textel.x, obj->material.texture->w), mod(textel.y, obj->material.texture->h));
	//color = getpixel(obj->texture, (int)u % obj->texture->w, (int)v %  obj->texture->h);
	ret.a = 255;
	SDL_GetRGB(color, obj->material.texture->format, &ret.r, &ret.g, &ret.b);
	return (ret);
}
