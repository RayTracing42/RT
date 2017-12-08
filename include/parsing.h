/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:47:13 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/26 14:41:39 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

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
char				*get_interval(const char *src, const char *start,
						const char *stop);
int					between(double value, double low_limit,
						double height_limit);

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
int					parsing_ambient_light(char *scene, t_scene *scn);
int					parsing_light(char *scene, t_scene *scn);

/*
**	parsing_objects.c
*/

t_plane				*parsing_plane(char *object);
t_sphere			*parsing_sphere(char *object);
t_cylinder			*parsing_cylinder(char *object);
t_cone				*parsing_cone(char *object);
int					parsing_object(char *scene, t_scene *scn);

/*
**	parsing_transformations.c
*/

t_trans_data		parsing_transformations(char *object);

/*
**	parsing_limit.c
*/

void				parsing_limit(t_object *obj, char *object, t_trans_data trans);

#endif
