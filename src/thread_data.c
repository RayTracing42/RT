//
//  thread_data.c
//  RT
//
//  Created by léo LELLOUCHE on 20/01/2018.
//  Copyright © 2018 léo LELLOUCHE. All rights reserved.
//

#include "rt.h"


/*
** La hauteur n'étant pas forcément un multiple de 4, il manque 1 ou 2 pixels
** à la fin. Ainsi, le dernier thread aura 1 ou 2 lignes en plus
*/
t_thread_data *init_thread_array(t_scene *scn, int nb_thread)
{
	t_thread_data	*threads;
	int				i;
	int				height_thread;
	t_ray			ray;
	
	threads = (t_thread_data *)malloc(sizeof(t_thread_data) * nb_thread);
	ray.equ.vc = *(t_vector*)&scn->cam->origin;
	ray.actual_refractive_i = 1;
	height_thread = WIN_HEIGHT/nb_thread;
	i = 0;
	while (i < nb_thread)
	{
		ray.limit = i;
		if (i == nb_thread - 1)
			threads[i] = thread_data((height_thread * i) - 1, WIN_HEIGHT, scn, ray);
		else
			threads[i] = thread_data((height_thread * i) - 1, height_thread * (i + 1), scn, ray);
		i++;
	}
	return threads;
}

t_thread_data thread_data(int y_begin, int y_end, t_scene *scn, t_ray ray)
{
	t_thread_data toRet;

	static SDL_mutex *mutex_put_pixel = NULL;
	static SDL_mutex *mutex_leaf = NULL;

	if (mutex_put_pixel == NULL)
		mutex_put_pixel = SDL_CreateMutex();
	if (mutex_leaf == NULL)
		mutex_leaf = SDL_CreateMutex();

	toRet.mutex_leaf = mutex_leaf;
	toRet.mutex_put_pixel = mutex_put_pixel;
	toRet.y_begin = y_begin;
	toRet.y_end = y_end;
	toRet.scn = scn;
	toRet.ray = ray;
	toRet.ray.tree = add_new_leaf(NULL, NULL, NULL, 0);

	return (toRet);
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
