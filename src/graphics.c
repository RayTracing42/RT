/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:52:28 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/24 11:15:53 by shiro            ###   ########.fr       */
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
	*core = (t_sdl_core){NULL, NULL, NULL, WIN_WIDTH, WIN_HEIGHT, 0, 0};
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

void		delete_sdl_core()
{
	/*int i;

	i = -1;
	while (++i < get_sdl_core(0)->nb_threads)
		SDL_DestroyTexture(get_sdl_core(i)->target);*/
	SDL_DestroyRenderer(get_sdl_core()->renderer);
	SDL_DestroyWindow(get_sdl_core()->window);
	SDL_Quit();
	free(get_sdl_core());
}

void		refresh_win(void)
{
	/*SDL_SetRenderTarget(get_sdl_core(0)->renderer, NULL);
	SDL_RenderCopy(get_sdl_core(0)->renderer, get_sdl_core(0)->target, NULL, NULL);*/
	SDL_RenderPresent(get_sdl_core()->renderer);
	//SDL_SetRenderTarget(get_sdl_core(0)->renderer, get_sdl_core(0)->target);
}

Uint32		get_color(int r, int g, int b)
{
	SDL_PixelFormat	*f;
	Uint32			col;

	f = SDL_AllocFormat(SDL_GetWindowPixelFormat(get_sdl_core()->window));
	col = SDL_MapRGB(f, r, g, b);
	SDL_FreeFormat(f);
	return (col);
}
