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

void		apply_duotone(SDL_Surface *screen, int x, int y, t_duotone t)
{
	SDL_Color curr;

	while (y < WIN_HEIGHT)
	{
  	while (x < WIN_WIDTH)
  	{
			curr = get_pixel_colors(screen, x, y);
			curr = (SDL_Color){((curr.r * t.c1.r) + ((256 - curr.r) * t.c2.r))/256,
				((curr.g * t.c1.g) + ((256 - curr.g) * t.c2.g))/256,
				((curr.b * t.c1.b) + ((256 - curr.b) * t.c2.b))/256, 255};
			put_pixel(x, y, &curr);
			x++;
  	}
		x = 0;
		y++;
	}
}

/*
** have to be preceded by the gray() function to work properly.
*/
int		duotone(SDL_Color col1, SDL_Color col2)
{
	SDL_Surface			*screen;
	t_duotone				tones;

	tones = (t_duotone){col1, col2};
	if ((screen = SDL_CreateRGBSurface(0,
					WIN_WIDTH, WIN_HEIGHT, 32, 0, 0, 0, 0)) == NULL)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	if (SDL_RenderReadPixels(get_sdl_core()->renderer, NULL,
				SDL_GetWindowPixelFormat(get_sdl_core()->window),
				screen->pixels, screen->pitch) != 0)
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	apply_duotone(screen, 0, 0, tones);
	return (0);
}
