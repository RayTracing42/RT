/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:36 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 16:45:43 by edescoin         ###   ########.fr       */
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
void		delete_sdl_core();
Uint32		get_color(int r, int g, int b);
t_sdl_core	*get_sdl_core();
void		refresh_win(t_scene *scn);

/*
** screenshot.c
*/
int		ft_access(const char *path);
char	*screenshot_name(int num);
char	*name_screen(void);
int		screenshot(void);

/*
** antialiasing.c
*/
SDL_Color			pixels_merger(SDL_Color pixel1, SDL_Color pixel2);
void		x4_antia(SDL_Surface *screen, int x, int y);
int		antia(void);

#endif
