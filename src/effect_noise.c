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

void		apply_noise(SDL_Surface *screen, int x, int y)
{
	SDL_Color curr;

	while (y < WIN_HEIGHT)
	{
  	while (x < WIN_WIDTH)
  	{
			curr = get_pixel_colors(screen, x, y);
			curr = (SDL_Color){((curr.r * 3) + (unsigned char)rand()) / 4,
			 	((curr.g * 3) + (unsigned char)rand()) / 4,
			 	((curr.b * 3) + (unsigned char)rand()) / 4, 255};
			put_pixel(x, y, &curr);
			x++;
  	}
		x = 0;
		y++;
	}
}

int		noise(void)
{
	SDL_Surface			*screen;

	if ((screen = SDL_CreateRGBSurface(0,
					WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
				SDL_GetWindowPixelFormat(get_sdl_core()->window),
				screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_noise(screen, 0, 0);
	return (0);
}
