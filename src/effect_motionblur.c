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

void		apply_motionblur(SDL_Surface *screen, int x, int y)
{
	SDL_Color curr;
	t_blur colors;

	while (y < get_sdl_core()->height)
	{
  	while (x < get_sdl_core()->width)
  	{
  		curr = get_pixel_colors(screen, x, y);
			colors = (t_blur){pixelaccess(screen, x + 8, y, curr), pixelaccess(screen, x + 12, y, curr),
						pixelaccess(screen, x - 8, y, curr), pixelaccess(screen, x - 12, y, curr),
						pixelaccess(screen, x + 2, y, curr), pixelaccess(screen, x + 4, y, curr),
							pixelaccess(screen, x - 2, y, curr), pixelaccess(screen, x - 4, y, curr), curr};
			curr = blur_color_picker(colors);
			put_pixel(x, y, &curr);
			x++;
  	}
		x = 0;
		y++;
	}
}

int		motionblur(void)
{
	SDL_Surface			*screen;

	if ((screen = SDL_CreateRGBSurface(0,
					get_sdl_core()->width, get_sdl_core()->height, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
				SDL_GetWindowPixelFormat(get_sdl_core()->window),
				screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_motionblur(screen, 0, 0);
	return (0);
}
