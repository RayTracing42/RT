/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:36 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/23 19:41:08 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "structures.h"
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include "SDL2/SDL.h"
# endif

/*
** graphics.c
*/
t_pxl_queue	*add_pxl_to_queue(int x, int y, SDL_Color col, t_pxl_queue **last);
void		add_end_pxl_to_queue(t_pxl_queue **last);
void		delete_sdl_core();
Uint32		get_color(int r, int g, int b);
t_sdl_core	*get_sdl_core();
void		put_pixel(int x, int y, SDL_Color *color);
void		refresh_win();
int			rendering_thread(void* data);
t_pxl_queue	**get_pxl_queue(int n);

#endif
