/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 10:59:52 by shiro             #+#    #+#             */
/*   Updated: 2018/01/24 11:08:13 by shiro            ###   ########.fr       */
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
void		put_pixel(int x, int y, SDL_Color *color)
{
	//SDL_LockMutex(mutex);
	if (color)
		SDL_SetRenderDrawColor(get_sdl_core()->renderer, color->r, color->g, color->b, color->a);
	SDL_RenderDrawPoint(get_sdl_core()->renderer, x, y);
	//SDL_UnlockMutex(mutex);
}

static void	update_pxl_queue(t_pxl_queue **list_queue, int nb_threads, int *nb_ended_threads)
{
	int	i;

	i = -1;
	while (++i < nb_threads)
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
			(*nb_ended_threads)++;
			list_queue[i]->rendered = -3;
		}
		else if (list_queue[i]->rendered && list_queue[i]->rendered != -3 && !(list_queue[i] + 1)->rendered)
			list_queue[i]++;
	}
}

int			rendering_thread(void* data)
{
	int	i;
	int	n;
	int	nb_ended_threads;
	t_pxl_queue	**list_queue;

	(void)data;
	n = get_sdl_core()->nb_threads;
	if (!(list_queue = malloc(n * sizeof(t_pxl_queue*))))
		exit_error("rt", "malloc");
	i = 0;
	while (++i <= n)
		list_queue[i - 1] = *get_pxl_queue(i);
	nb_ended_threads = 0;
	while (nb_ended_threads != n)
		update_pxl_queue(list_queue, n, &nb_ended_threads);
	return (0);
}
