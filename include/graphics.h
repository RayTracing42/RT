/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:36 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/05 23:50:23 by fcecilie         ###   ########.fr       */
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
void		put_pixel(int x, int y, SDL_Color *color);
void		refresh_win();

/*
** screenshot.c
*/
int		ft_access(const char *path);
char	*screenshot_name(int num);
char	*name_screen(void);
int		screenshot(void);

#endif
