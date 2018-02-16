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

void		apply_sepia(SDL_Surface *screen, int x, int y)
{
	SDL_Color curr;
	SDL_Color c;

	while (y < get_sdl_core()->height)
	{
  	while (x < get_sdl_core()->width)
  	{
  		curr = get_pixel_colors(screen, x, y);
			c = curr;
			if ((c.r * .393) + (c.g *.769) + (c.b * .189) > 255)
			curr.r = 255;
			else
			curr.r = (c.r * .393) + (c.g *.769) + (c.b * .189);

			if ((c.r * .349) + (c.g *.686) + (c.b * .168) > 255)
			curr.g = 255;
			else
			curr.g = (c.r * .349) + (c.g *.686) + (c.b * .168);

			if ((c.r * .272) + (c.g *.534) + (c.b * .131) > 255)
			curr.b = 255;
			else
			curr.b = (c.r * .272) + (c.g *.534) + (c.b * .131);

			curr.a = 255;
			put_pixel(x, y, &curr);
			x++;
  	}
		x = 0;
		y++;
	}
}

int		sepia(void)
{
	SDL_Surface			*screen;

//gray();
	if ((screen = SDL_CreateRGBSurface(0,
					get_sdl_core()->width, get_sdl_core()->height, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
				SDL_GetWindowPixelFormat(get_sdl_core()->window),
				screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_sepia(screen, 0, 0);
	return (0);
}
