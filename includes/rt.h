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
#  include <SDL2/SDL.h>
#  define SDL_VIDEO		SDL_INIT_VIDEO
# else
#  include "SDL2/SDL.h"
#  define SDL_VIDEO		SDL_VIDEO_DRIVER_COCOA
# endif

# define TITLE			"RT"

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include "camera.h"
# include "events.h"
# include "graphics.h"
# include "libft.h"
# include "lights.h"
# include "objects.h"
# include "scene.h"
# include "structures.h"

t_vector	matrice_rotation_x(t_vector *m, double angle);
t_vector	matrice_rotation_y(t_vector *m, double angle);
t_vector	matrice_rotation_z(t_vector *m, double angle);

t_vector	vector(double x, double y, double z);
t_vector	vector_opposite(double x, double y, double z);
t_dot		dot(double x, double y, double z);
double		delta(double a, double b, double c);
double		angle_between_vectors(t_vector a, t_vector b);

void		view_plane(t_camera *cam, t_view_plane *vp);
void		view_plane_vector(int x, int y, t_camera *cam, t_vector *vd);

int			parsing(t_scene *scn, int argc, char **argv);

int			scanning(t_scene *scn);

SDL_Color	get_shade_col(t_ray *ray, const t_scene *scene);

/*
**	tools.c
*/
int			get_quad_equation_sol(t_dot *res, double a, double b, double c);
void		set_rect_dim(SDL_Rect *rect, int w, int h);
void		set_rect_crd(SDL_Rect *rect, int x, int y);

/*
**	vectors.c
*/

double		vect_dot_product(const t_vector *v1, const t_vector *v2);
double		get_vect_lenght(const t_vector *vect);

#endif
