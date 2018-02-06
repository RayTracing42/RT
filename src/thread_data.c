/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llellouc <llellouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:32:58 by llellouc          #+#    #+#             */
/*   Updated: 2018/02/03 14:19:39 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_thread_data	thread_data(int y_begin, int y_end, t_scene *scn, int n_thread)
{
	t_thread_data	toRet;

	toRet.y_begin = y_begin;
	toRet.y_end = y_end;
	toRet.scn = *scn;
	toRet.n_thread = n_thread;

	return (toRet);
}

static void		init_pxl_queue(t_thread_data *threads, int i)
{
	int				j;
	t_pxl_queue		**tmp;

	tmp = get_pxl_queue(i + 1);
	if (!((*tmp) = malloc(((threads[i].y_end - threads[i].y_begin - 1) * WIN_WIDTH + 1) * sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	j = -1;
	while (++j < (threads[i].y_end - threads[i].y_begin - 1) * WIN_WIDTH)
		(*tmp)[j].rendered = -2;
	(*tmp)[j].rendered = -1;
}

/*
** La hauteur n'étant pas forcément un multiple de 4, il manque 1 ou 2 pixels
** à la fin. Ainsi, le dernier thread aura 1 ou 2 lignes en plus
*/
t_thread_data	*init_thread_array(t_scene *scn, int nb_thread)
{
	t_thread_data	*threads;
	int				i;
	int				height_thread;

	if (!(threads = (t_thread_data*)malloc(sizeof(t_thread_data) * nb_thread)))
		exit_error("rt", "malloc");
	height_thread = WIN_HEIGHT / nb_thread;
	i = -1;
	while (++i < nb_thread - 1)
	{
		threads[i] = thread_data((height_thread * i) - 1, height_thread * (i + 1), scn, i + 1);
		init_pxl_queue(threads, i);
	}
	threads[i] = thread_data((height_thread * i) - 1, WIN_HEIGHT, scn, i + 1);
	init_pxl_queue(threads, i);
	return (threads);
}

t_mutexes	*get_mutexes()
{
	static t_mutexes	*mutex = NULL;

	if (!mutex)
	{
		if (!(mutex = malloc(sizeof(t_mutexes))))
			exit_error("rt", "malloc");
		if (!(mutex->intersect = SDL_CreateMutex()))
			exit_error("rt", "SDL_CreateMutex");
	}
	return (mutex);
}
