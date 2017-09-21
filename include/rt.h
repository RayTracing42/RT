/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 10:49:54 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 19:49:47 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# ifndef __APPLE__
#  include <SDL2/SDL.h>
#  define SDL_VIDEO		SDL_INIT_VIDEO
# else
#  include "SDL2/SDL.h"
#  define SDL_VIDEO		SDL_VIDEO_DRIVER_COCOA
# endif

# define TITLE			"RTv1"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "events.h"
# include "graphics.h"
# include "libft.h"
# include "lights.h"
# include "objects.h"
# include "structures.h"


/*
** tools.c
*/
int		get_quad_equation_sol(t_dot *res, double a, double b, double c);
void	set_rect_dim(SDL_Rect *rect, int w, int h);
void	set_rect_crd(SDL_Rect *rect, int x, int y);

#endif
