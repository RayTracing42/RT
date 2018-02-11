/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 10:49:54 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/11 11:45:32 by shiro            ###   ########.fr       */
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

# define TITLE			"RT"
# define POW			10000000000
# define EMPTY			0
# define FULL			1
# define NONE			2

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <sys/timeb.h>

# include "camera.h"
# include "equations.h"
# include "events.h"
# include "graphics.h"
# include "../libraries/libft/includes/libft.h"
# include "intersections.h"
# include "lights.h"
# include "light_shading.h"
# include "limit.h"
# include "list_ray.h"
# include "matrix.h"
# include "negative_obj.h"
# include "objects.h"
# include "parsing.h"
# include "reflection.h"
# include "reflect_refract_tree.h"
# include "refraction.h"
# include "rendering.h"
# include "scanning.h"
# include "scene.h"
# include "structures.h"
# include "textures.h"
# include "thread_data.h"
# include "vectors.h"
# include "vectors_transformations.h"

/*
**	utils.c
*/
int				eq(double nb1, double nb2);
int				ge(double nb1, double nb2);
int				get_status(char *status);
int				gt(double nb1, double nb2);
int				le(double nb1, double nb2);
int				lt(double nb1, double nb2);

#endif
