/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/14 12:38:34 by shiro            ###   ########.fr       */
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

void	spherical_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	textel->x = 0.5 + ((atan2(-i.x,  -i.z)) / (2 * M_PI));
	textel->y = (acos(i.y)) / (M_PI);
	textel->x *= texture->w * streching;
	textel->y *= texture->h * streching;
}

void	cylindrical_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	textel->x = 0.5 + (atan2(i.x,  i.z) / (2 * M_PI));
	textel->x *= texture->w * streching;
	i.y /= sqrt(i.x * i.x + i.z * i.z);
	textel->y = mod(i.y * texture->h * streching, texture->h);
}

void	planar_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	textel->x = mod(i.z * texture->w * streching, texture->w);
	textel->y = mod(i.y * texture->h * streching, texture->h);
}

SDL_Color getTextColor(t_dot pt, t_object *obj)
{
	t_dot	textel;
	Uint32 color;
	SDL_Color	ret;

	vect_normalize((t_vector*)&pt);
	obj->material.texture_mapping(pt, &textel, obj->material.txt_streching, obj->material.texture);
	color = getpixel(obj->material.texture, mod(textel.x, obj->material.texture->w), mod(textel.y, obj->material.texture->h));
	SDL_GetRGB(color, obj->material.texture->format, &ret.r, &ret.g, &ret.b);
	ret.a = 255;
	return (ret);
}

t_vector	getMapVector(t_dot pt, t_object *obj)
{
	t_dot		textel;
	SDL_Color	tmp;
	Uint32		color;

	pt.x -= obj->origin.x;
	pt.y -= obj->origin.y;
	pt.z -= obj->origin.z;
	vect_normalize((t_vector*)&pt);
	obj->material.map_mapping(pt, &textel, obj->material.map_streching, obj->material.normal_map);
	color = GetPixel32(obj->material.normal_map, mod(textel.x, obj->material.normal_map->w), mod(textel.y, obj->material.normal_map->h));
	//color = getpixel(obj->texture, (int)u % obj->texture->w, (int)v %  obj->texture->h);
	SDL_GetRGB(color, obj->material.normal_map->format, &tmp.r, &tmp.g, &tmp.b);
	return ((t_vector){((int)(tmp.r)) / 255.0, ((int)(tmp.g)) / 255.0, (((int)tmp.b)) / 255.0});
}
