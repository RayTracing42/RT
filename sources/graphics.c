/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:52:28 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 10:57:21 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sdl_core	*get_sdl_core(void)
{
	static t_sdl_core	*core = NULL;

	if (core)
		return (core);
	if (!(core = malloc(sizeof(t_sdl_core))))
		exit_error("rt", "malloc");
	*core = (t_sdl_core){NULL, NULL, WIN_WIDTH, WIN_HEIGHT, 0};
	if (SDL_Init(SDL_VIDEO) ||
		!(core->window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WIN_WIDTH, WIN_HEIGHT,
										SDL_WINDOW_SHOWN)) ||
		!(core->renderer = SDL_CreateRenderer(core->window, -1,
											SDL_RENDERER_ACCELERATED)))
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	return (core);
}

void		delete_sdl_core(void)
{
	SDL_DestroyWindow(get_sdl_core()->window);
	SDL_DestroyRenderer(get_sdl_core()->renderer);
	SDL_Quit();
	free(get_sdl_core());
}

void		refresh_win(void)
{
	SDL_RenderPresent(get_sdl_core()->renderer);
}

Uint32		get_color(int r, int g, int b)
{
	return (SDL_MapRGB(SDL_AllocFormat(SDL_GetWindowPixelFormat(
										get_sdl_core()->window)),
						r, g, b));
}

void		put_pixel(int x, int y, SDL_Color *color)
{
	if (color)
		SDL_SetRenderDrawColor(get_sdl_core()->renderer, color->r, color->g,
								color->b, color->a);
	SDL_RenderDrawPoint(get_sdl_core()->renderer, x, y);
}
