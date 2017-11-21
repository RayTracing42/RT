/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 10:49:54 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/20 20:33:25 by shiro            ###   ########.fr       */
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
# include <fcntl.h>
# include "camera.h"
# include "events.h"
# include "graphics.h"
# include "libft.h"
# include "lights.h"
# include "light_physic.h"
# include "light_shading.h"
# include "matrix.h"
# include "objects.h"
# include "scene.h"
# include "structures.h"
# include "vectors.h"
# include "parsing.h"

t_vector	matrice_rotation_x(t_vector *m, double angle);
t_vector	matrice_rotation_y(t_vector *m, double angle);
t_vector	matrice_rotation_z(t_vector *m, double angle);

t_vector	vector(double x, double y, double z);
t_vector	vector_opposite(double x, double y, double z);
t_dot		dot(double x, double y, double z);
double		delta(double a, double b, double c, int *n);
double		angle_between_vectors(t_vector a, t_vector b);

void		view_plane(t_camera *cam, t_view_plane *vp);
void		view_plane_vector(int x, int y, t_camera *cam, t_vector *vd);

void			scanning(t_scene *scn);
t_parequation	transform_equ(t_ray *ray, t_object *obj);
void			transform_inter(t_ray *ray, t_object *obj);

SDL_Color	effects(t_ray *ray, t_scene *scn);
SDL_Color	shadows(t_ray *ray, t_scene *scn);
SDL_Color	reflect(t_ray *ray, t_scene *scn);
SDL_Color	refract(t_ray *ray, t_scene *scn);

/*
**	refract_list.c
*/

void		add_node(t_list_objs **l, t_object *obj);
void		remove_node(t_list_objs **l, t_object *obj);
int			if_node_exist(t_list_objs *l, t_object *obj);


/*
**	tools.c
*/
t_dot		equation_get_dot(t_parequation *eq, double t);
int			get_quad_equation_sol(double *res, double a, double b, double c);
int			gt_0(double nb);

/*
**	vectors.c
*/

double		vect_dot_product(const t_vector *v1, const t_vector *v2);
double		get_vect_lenght(const t_vector *vect);
double		get_dot_dist(t_dot *d1, t_dot *d2);

#endif
