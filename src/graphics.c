/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:52:28 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/23 22:30:28 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_pxl_queue	**get_pxl_queue(int n)
{
	static t_pxl_queue	**queue = NULL;
	static int nb_threads = 0;

	if (queue)
	{
		if (n <= nb_threads && n > 0)
			return (&queue[n - 1]);
		else
			return (NULL);
	}
	if (!(queue = malloc(n * sizeof(t_pxl_queue*))))
		exit_error("rt", "malloc");
	ft_bzero(queue, n * sizeof(t_pxl_queue*));
	nb_threads = n;
	return (queue);
}
/*
void	add_pxl_to_queue(int x, int y, SDL_Color col, t_pxl_queue **last)
{
	t_pxl_queue	*tmp;

	if (!(tmp = malloc(sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	*tmp = (t_pxl_queue){0, x, y, col, NULL};
	if (*last)
		(*last)->next = tmp;
	else
		*last = tmp;
	return (tmp);
}

void		add_end_pxl_to_queue(t_pxl_queue **last)
{
	t_pxl_queue	*tmp;

	if (!(tmp = malloc(sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	printf("TEST\n");
	*tmp = (t_pxl_queue){-1, 0, 0, (SDL_Color){0, 0, 0, 0}, NULL};
	if (*last)
		(*last)->next = tmp;
	else
		*last = tmp;
}
*/
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

void		put_pixel(int x, int y, SDL_Color *color)
{
	//SDL_LockMutex(mutex);
	if (color)
		SDL_SetRenderDrawColor(get_sdl_core()->renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawPoint(get_sdl_core()->renderer, x, y);
	//SDL_UnlockMutex(mutex);
}

int			rendering_thread(void* data)
{
	const int	n = get_sdl_core()->nb_threads;
	int	i;
	int	nb_ended_threads;
	t_pxl_queue	**list_queue;

	(void)data;
	if (!(list_queue = malloc(n * sizeof(t_pxl_queue*))))
		exit_error("rt", "malloc");
	i = 0;
	while (++i <= n)
		list_queue[i - 1] = *get_pxl_queue(i);
	nb_ended_threads = 0;
	while (nb_ended_threads != n)
	{
		i = -1;
		while (++i < n)
		{
			if (!list_queue[i]->rendered)
			{
				put_pixel(list_queue[i]->x, list_queue[i]->y, &list_queue[i]->col);
				if ((list_queue[i] + 1)->rendered >= -1)
					list_queue[i]++;
				else
					list_queue[i]->rendered = 1;
			}
			else if (list_queue[i]->rendered == -1)
			{
				nb_ended_threads++;
				list_queue[i]->rendered = -3;
			}
			else if (list_queue[i]->rendered && list_queue[i]->rendered != -3 && !(list_queue[i] + 1)->rendered)
				list_queue[i]++;
		}
	}
	return (0);
}
