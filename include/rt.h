/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 10:49:54 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/31 05:47:03 by fcecilie         ###   ########.fr       */
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
# include "camera.h"
# include "events.h"
# include "graphics.h"
# include "libft.h"
# include "lights.h"
# include "light_physic.h"
# include "light_shading.h"
# include "matrix.h"
# include "objects.h"
# include "reflect_refract_tree.h"
# include "scene.h"
# include "structures.h"
# include "vectors.h"
# include "parsing.h"

t_vector		matrice_rotation_x(t_vector *m, double angle);
t_vector		matrice_rotation_y(t_vector *m, double angle);
t_vector		matrice_rotation_z(t_vector *m, double angle);

void			view_plane(t_camera *cam, t_view_plane *vp);
void			view_plane_vector(int x, int y, t_camera *cam, t_vector *vd);

t_ray			first_intersect(const t_ray *ray, t_object *obj, double *tmp);
t_ray			second_intersect(const t_ray *ray, t_object *obj, double *tmp);
double			check_intersect(t_ray *ray, t_list_objs *l_objs);

void			scanning(t_scene *scn);
t_parequation	transform_equ(t_ray *ray, t_object *obj);
void			transform_inter(t_ray *ray, t_object *obj);
void			valid_ray(t_ray *r1, double *t_r1, t_ray *r2, double *t_r2);

SDL_Color		effects(t_ray *ray, t_scene *scn);
SDL_Color		shadows(t_ray *ray, t_scene *scn);
SDL_Color		reflect(t_ray *ray, t_scene *scn);
SDL_Color		refract(t_ray *ray, t_scene *scn);

/*
**	refract_list.c
*/

void			add_node(t_list_objs **l, t_object *obj);
void			remove_node(t_list_objs **l, t_object *obj);
int				if_node_exist(t_list_objs *l, t_object *obj);


/*
**	tools.c
*/
t_dot			equation_get_dot(t_parequation *eq, double t);
int				get_quad_equation_sol(double *res, double fac[4], int i);
int				gt(double nb1, double nb2);
int				lt(double nb1, double nb2);
int				eq(double nb1, double nb2);
int				ge(double nb1, double nb2);
int				le(double nb1, double nb2);

/*
**	utils.c
*/

t_vector			vector(double x, double y, double z);
t_dot				dot(double x, double y, double z);
double				angle_between_vectors(t_vector a, t_vector b);
int					get_status(char *status);

/*
**	limit.c // limit2.c
*/

void			limit(t_couple_ray *basic, t_object *father, const t_ray *ray);
void			limit2(t_couple_ray *limited, t_ray *tmp, double *t_tmp);
int				is_in_limit(const t_ray *ray, t_object *father);

/*
**	negative_obj.c
*/

void			negative_obj(t_list_ray **l_ray, t_couple_ray *basic, t_object *father, const t_ray *ray);



int		is_in_obj(const double t, const t_dot inter, t_object *obj);
int		is_in_limited_obj(const double *t, const t_ray *ray, t_object *obj);

void	unvalid_point_in_limit(t_couple_ray *basic, t_object *father);
void	unvalid_point_in_negative_obj(t_couple_ray *couple, t_object *father,
	t_ray *ray);

void	add_cell_ray(t_list_ray **head, t_ray *ray, double *dist);
void	delete_cell_ray(t_list_ray **cell);

#endif
