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

t_blur 	surrounding_pixels(SDL_Surface *screen, int x, int y)
{
	t_blur 		b;
	SDL_Color curr;

	curr = get_pixel_colors(screen, x, y);
	b = (t_blur){get_pixel_colors(screen, x - 1, y - 1),
		get_pixel_colors(screen, x + 1, y - 1),
		get_pixel_colors(screen, x - 1, y + 1),
		get_pixel_colors(screen, x + 1, y + 1),
		get_pixel_colors(screen, x, y - 1),
		get_pixel_colors(screen, x, y + 1),
		get_pixel_colors(screen, x - 1, y),
		get_pixel_colors(screen, x + 1, y), curr};
		return (b);
}

void		apply_laplacian(SDL_Surface *screen, int x, int y)
{
	SDL_Color 	curr;
	t_blur			b;
	SDL_Surface *screensav;

	screensav = screen;
	while (y < get_sdl_core()->height)
	{
  	while (x < get_sdl_core()->width)
  	{
			curr = get_pixel_colors(screen, x, y);
			b = surrounding_pixels(screensav, x ,y);
			curr = (SDL_Color){(curr.r * 4) - (b.tl1.r + b.tr1.r + b.bl1.r + b.br1.r),
			 	(curr.g * 4) - (b.tl1.g + b.tr1.g + b.bl1.g + b.br1.g),
			 	(curr.b * 4) - (b.tl1.b + b.tr1.b + b.bl1.b + b.br1.b), 255};
			put_pixel(x, y, &curr);
			x++;
  	}
		x = 0;
		y++;
	}
}

int		laplacian(void)
{
	SDL_Surface			*screen;

	if ((screen = SDL_CreateRGBSurface(0,
					get_sdl_core()->width, get_sdl_core()->height, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
				SDL_GetWindowPixelFormat(get_sdl_core()->window),
				screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_laplacian(screen, 0, 0);
	return (0);
}
