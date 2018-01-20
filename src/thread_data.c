//
//  thread_data.c
//  RT
//
//  Created by léo LELLOUCHE on 20/01/2018.
//  Copyright © 2018 léo LELLOUCHE. All rights reserved.
//

#include "rt.h"

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
	
	return (toRet);
}


