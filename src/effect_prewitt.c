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

	// get_pixel_colors(screen, x - 1, y - 1), tl1
	// get_pixel_colors(screen, x + 1, y - 1),	tr1
	// get_pixel_colors(screen, x - 1, y + 1),	bl1
	// get_pixel_colors(screen, x + 1, y + 1), br1
	// get_pixel_colors(screen, x, y - 1),			tl2
	// get_pixel_colors(screen, x, y + 1),			tr2
	// get_pixel_colors(screen, x - 1, y),			bl2
	// get_pixel_colors(screen, x + 1, y), 		br2

void		apply_prewitt(SDL_Surface *screen, int x, int y)
{
	SDL_Color 	curr;
	t_blur			b;

	while (y < WIN_HEIGHT)
	{
  	while (x < WIN_WIDTH)
  	{
			b = surrounding_pixels(screen, x ,y);
			curr = (SDL_Color){(b.tr1.r + b.br1.r + b.br2.r) - (b.tl1.r + b.bl1.r + b.bl2.r),
			 	(b.tr1.g + b.br1.g + b.br2.g) - (b.tl1.g + b.bl1.g + b.bl2.g),
			 	(b.tr1.b + b.br1.b + b.br2.b) - (b.tl1.b + b.bl1.b + b.bl2.b), 255};
			curr = (SDL_Color){(b.tl1.r + b.tr1.r + b.tl2.r) - (b.bl1.r + b.br1.r + b.tr2.r),
			 	(b.tl1.g + b.tr1.g + b.tl2.g) - (b.bl1.g + b.br1.g + b.tr2.g),
			 	(b.tl1.b + b.tr1.b + b.tl2.b) - (b.bl1.b + b.br1.b + b.tr2.b), 255};
			put_pixel(x, y, &curr);
			x++;
  	}
		x = 0;
		y++;
	}
}

int		prewitt(void)
{
	SDL_Surface			*screen;

	if ((screen = SDL_CreateRGBSurface(0,
					WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
				SDL_GetWindowPixelFormat(get_sdl_core()->window),
				screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_prewitt(screen, 0, 0);
	return (0);
}