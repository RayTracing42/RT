/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 10:49:54 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/06 00:52:46 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# ifndef __APPLE__
#  include <../SDL2/include/SDL.h>
#  define SDL_VIDEO		SDL_INIT_VIDEO
# else
#  include "../SDL2/include/SDL.h"
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



#endif
