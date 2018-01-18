/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:47:13 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/18 13:08:49 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "structures.h"

/*
**	parsing.c
*/

int					parsing_vector(char *data_vector, t_vector *d);
int					parsing_dot(char *data_dot, t_dot *d);
int					parsing_color(char *data_color, SDL_Color *c);
int					parsing_physic(char *data_physic, t_objs_comp *args);
t_scene				*parsing(int argc, char **argv);

/*
**	parsing_tools.c
*/

double				int_to_decimal(int n);
double				atod(char *src);
char				*get_interval(char *src, const char *start, const char *stop);
int					between(double value, double low_limit,
						double height_limit);
int					get_nb_occ(const char *src, const char *occ, int lim);

/*
**	parsing_scene.c
*/

t_scene				*parsing_scene(char *scene);

/*
**	parsing_camera.c
*/

t_camera			*parsing_camera(char *scene);

/*
**	parsing_lights.c
*/

t_parallel_light	*parsing_parallel_light(char *light);
t_spotlight			*parsing_spotlight(char *light);
t_orb_light			*parsing_orb_light(char *light);
t_list_lights		*parsing_light(char *scene);

/*
**	parsing_objects.c
*/

t_plane				*parsing_plane(char *object);
t_sphere			*parsing_sphere(char *object);
t_cylinder			*parsing_cylinder(char *object);
t_cone				*parsing_cone(char *object);
t_list_objs			*parsing_object(char *scene);
t_object			*parsing_object2(char *object);

/*
**	parsing_transformations.c
*/

void				parsing_transformations(t_object *obj, char *trans);

/*
**	parsing_limit.c
*/

void				parsing_limit(t_object *obj, char *object);

/*
**	parsing_negative_obj.c
*/

void				parsing_negative_obj(t_object *obj, char *object);

#endif
