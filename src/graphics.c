/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:52:28 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/23 15:08:56 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_sdl_core	*get_sdl_core(int n)
{
	static t_sdl_core	*core = NULL;
	int i;

	if (core)
	{
		if (n < core[0].nb_threads && n >= 0)
			return (&core[n]);
		else
			return (NULL);
	}
	if (n <= 0)
		n = 1;
	if (!(core = malloc(n * sizeof(t_sdl_core))))
		exit_error("rt", "malloc");
	if (SDL_Init(SDL_VIDEO) ||
		!(core[0].window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WIN_WIDTH, WIN_HEIGHT,
										SDL_WINDOW_SHOWN)))
		exit_custom_error("rt: Erreur SDL2: ", (char*)SDL_GetError());
	i = -1;
	while (++i < n)
	{
		core[i] = (t_sdl_core){core[0].window, SDL_CreateRenderer(core[0].window, -1, SDL_RENDERER_ACCELERATED), n, WIN_WIDTH, WIN_HEIGHT, 0};
		if (!(core[i]).renderer)
			exit_custom_error("rt: Erreur SDL2: ", (char*)SDL_GetError());
	}
	return (core);
}

void		delete_sdl_cores()
{
	int i;

	i = -1;
	while (++i < get_sdl_core(0)->nb_threads)
		SDL_DestroyRenderer(get_sdl_core(i)->renderer);
	SDL_DestroyWindow(get_sdl_core(0)->window);
	SDL_Quit();
	free(get_sdl_core(0));
}

void		refresh_win(void)
{
	int i;

	i = -1;
	while (++i < get_sdl_core(0)->nb_threads)
		SDL_RenderPresent(get_sdl_core(i)->renderer);
}

Uint32		get_color(int r, int g, int b)
{
	SDL_PixelFormat	*f;
	Uint32			col;

	f = SDL_AllocFormat(SDL_GetWindowPixelFormat(get_sdl_core(0)->window));
	col = SDL_MapRGB(f, r, g, b);
	SDL_FreeFormat(f);
	return (col);
}

void		put_pixel(int n_thread, int x, int y, SDL_Color *color)
{
	if (color)
		SDL_SetRenderDrawColor(get_sdl_core(n_thread)->renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawPoint(get_sdl_core(n_thread)->renderer, x, y);
}
