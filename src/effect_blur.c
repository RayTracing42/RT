/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur_effect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joinacio <joinacio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2017/12/07 04:18:03 by joinacio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

SDL_Color 	get_pixel_colors(SDL_Surface *screen, int x, int y)
{
	SDL_Color				rgba;

	rgba = (SDL_Color){0, 0, 0, 0};
	SDL_GetRGBA(((int*)screen->pixels)[x + (y * get_sdl_core()->width)],
	screen->format, &rgba.r, &rgba.g, &rgba.b, &rgba.a);
	return (rgba);
}

SDL_Color		pixelaccess(SDL_Surface *s, int x, int y, SDL_Color curr)
{
	if (x - 1 < 0 || y - 1 < 0 || x + 1 > get_sdl_core()->width || y + 1 > get_sdl_core()->height)
		return(curr);
	return (get_pixel_colors(s, x, y));
}

SDL_Color 	blur_color_picker(t_blur c)
{
		SDL_Color current;

		current = (SDL_Color){((c.tl1.r + c.tr1.r + c.bl1.r + c.br1.r) / 4 +
												c.tl2.r + c.tr2.r + c.bl2.r + c.br2.r  + c.curr.r) / 6,
												((c.tl1.g + c.tr1.g + c.bl1.g + c.br1.g) / 4 +
												c.tl2.g + c.tr2.g + c.bl2.g + c.br2.g + c.curr.g) / 6,
												((c.tl1.b + c.tr1.b + c.bl1.b + c.br1.b) / 4 +
												c.tl2.b + c.tr2.b + c.bl2.b + c.br2.b  + c.curr.b) / 6, 255};
		return (current);
}

void		apply_blur(SDL_Surface *screen, int x, int y)
{
	SDL_Color curr;
	t_blur colors;

	while (y < get_sdl_core()->height)
	{
  	while (x < get_sdl_core()->width)
  	{
  		curr = get_pixel_colors(screen, x, y);
			colors = (t_blur){pixelaccess(screen, x, y + 2, curr), pixelaccess(screen, x + 2, y, curr),
						pixelaccess(screen, x - 2, y, curr), pixelaccess(screen, x, y + 2, curr),
						pixelaccess(screen, x, y + 1, curr), pixelaccess(screen, x + 1, y, curr),
							pixelaccess(screen, x - 1, y, curr), pixelaccess(screen, x, y + 1, curr), curr};
			curr = blur_color_picker(colors);
			put_pixel(x, y, &curr);
			x++;
  	}
		x = 0;
		y++;
	}
}

int		blur(void)
{
	SDL_Surface			*screen;

	if ((screen = SDL_CreateRGBSurface(0,
					get_sdl_core()->width, get_sdl_core()->height, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
				SDL_GetWindowPixelFormat(get_sdl_core()->window),
				screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_blur(screen, 0, 0);
	return (0);
}
