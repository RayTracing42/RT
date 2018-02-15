/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/15 13:13:15 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

/*Uint32 GetPixel32(SDL_Surface *image, int i, int j)
{
	if (i < 0 || i > image-> w - 1 || j < 0 || j > image-> h - 1)
		return 0;
	return (((Uint32*)(image->pixels))[j * (image->pitch / 4) + i]);
}*/

static Uint32	getpixel(SDL_Surface *surface, int x, int y, int *err)
{
	int		bpp;
	Uint8	*p;

	if (x >= surface->w ||  y >= surface->h || x < 0 || y < 0)
	{
		*err = 1;
		return (0);
	}
	else
		*err = 0;
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
	*err = 1;
	return (0);
}

void	spherical_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	int w;
	int h;

	vect_normalize((t_vector*)&i);
	w = texture ? texture->w : 2;
	h = texture ? texture->h : 1;
	textel->x = 0.5 + ((atan2(-i.x,  -i.z)) / (2 * M_PI));
	textel->y = (acos(i.y)) / (M_PI);
	textel->x *= w * streching;
	textel->y *= h * streching;
}

void	cylindrical_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	int w;
	int h;

	w = texture ? texture->w : 2;
	h = texture ? texture->h : 1;
	vect_normalize((t_vector*)&i);
	textel->x = 0.5 + (atan2(-i.x,  -i.z) / (2 * M_PI));
	textel->x *= w * streching;
	i.y /= sqrt(i.x * i.x + i.z * i.z);
	if (texture)
		textel->y = -i.y * h * (streching / (2 * M_PI));
	else
		textel->y = i.y * streching;
}

void	planar_mapping_x(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	int w;
	int h;

	w = texture ? texture->w : 1;
	h = texture ? texture->h : 1;
	if (texture)
		*textel = (t_dot){i.z * w * (streching / (2 * M_PI)), -i.y * h * (streching / (2 * M_PI)), 0};
	else
		*textel = (t_dot){i.z * streching, i.y * streching, 0};
}

void	planar_mapping_y(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	int w;
	int h;

	w = texture ? texture->w : 1;
	h = texture ? texture->h : 1;
	if (texture)
		*textel = (t_dot){i.x * w * (streching / (2 * M_PI)), -i.z * h * (streching / (2 * M_PI)), 0};
	else
		*textel = (t_dot){i.x * streching, i.z * streching, 0};
}

void	planar_mapping_z(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	int w;
	int h;

	w = texture ? texture->w : 1;
	h = texture ? texture->h : 1;
	if (texture)
		*textel = (t_dot){i.y * w * (streching / (2 * M_PI)), -i.x * h * (streching / (2 * M_PI)), 0};
	else
		*textel = (t_dot){i.y * streching, i.x * streching, 0};
}

void	planar_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture)
{
	planar_mapping_x(i, textel, streching, texture);
}

SDL_Color	getTextColor(t_dot pt, t_object *obj)
{
	t_dot		textel;
	Uint32		color;
	SDL_Color	ret;
	int			err;

	obj->material.texture_mapping(pt, &textel, obj->material.txt_streching, obj->material.texture);
	if (obj->material.texture)
	{
		if (obj->material.txt_repeat)
			textel = (t_dot){mod(textel.x, obj->material.texture->w),
							mod(textel.y, obj->material.texture->h), 0};
		color = getpixel(obj->material.texture, textel.x, textel.y, &err);
		if (err)
			ret = obj->material.color;
		else
			SDL_GetRGB(color, obj->material.texture->format, &ret.r, &ret.g, &ret.b);
	}
	else
	{
		if ((textel.x < 0 && textel.y >= 0) || (textel.y <= 0 && textel.x > 0))
			ret = (mod(textel.x, 2) && !mod(textel.y, 2)) || (!mod(textel.x, 2) && mod(textel.y, 2)) ? (SDL_Color){255, 255, 255, 255} : (SDL_Color){0, 0, 0, 255};
		else
			ret = (mod(textel.x, 2) && !mod(textel.y, 2)) || (!mod(textel.x, 2) && mod(textel.y, 2)) ? (SDL_Color){0, 0, 0, 255} : (SDL_Color){255, 255, 255, 255};
	}
	ret.a = 255;
	return (ret);
}

t_vector	getMapVector(t_dot pt, t_object *obj)
{
	t_dot		textel;
	SDL_Color	tmp;
	Uint32		color;
	int			err;

	obj->material.map_mapping(pt, &textel, obj->material.map_streching, obj->material.normal_map);
	if (obj->material.map_repeat)
		textel = (t_dot){mod(textel.x, obj->material.normal_map->w),
						mod(textel.y, obj->material.normal_map->h), 0};
	color = getpixel(obj->material.normal_map, textel.x, textel.y, &err);
	if (err)
		return ((t_vector){1, 1, 1});
	SDL_GetRGB(color, obj->material.normal_map->format, &tmp.r, &tmp.g, &tmp.b);
	return ((t_vector){((int)(tmp.r)) / 255.0, ((int)(tmp.g)) / 255.0, (((int)(tmp.b - 128))) / 255.0});
}
