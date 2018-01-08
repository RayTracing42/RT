/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:47:13 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/08 17:44:00 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "structures.h"

/*
** objects*.c
*/
void		delete_object(t_object *obj);
t_object	*new_object(t_type type, t_objs_comp args);
void		set_object_color(t_object *obj, int r, int g, int b);

void		rotate_object(t_object *obj, double x_angle, double y_angle,
						double z_angle);
void		scale_object(t_object *obj, double x, double y, double z);
void		set_all_matrix(t_object *object, t_trans_data data);
void		translate_object(t_object *obj, double x, double y, double z);

/*
** box.c
*/
/*t_box		*new_box(t_dot fbl_corner, double x_width, double y_width,
					double z_width);*/

/*
** cone.c
*/
void		delete_cone(t_cone *cone);
t_cone		*new_cone(t_objs_comp args, double angle);

/*
** cylinder.c
*/
void		delete_cylinder(t_cylinder *cylinder);
t_cylinder	*new_cylinder(t_objs_comp args, double radius);

/*
** plane.c
*/
void		delete_plane(t_plane *plane);
t_plane		*new_plane(t_objs_comp args, t_vector normal, int tgl);
double		plane_intersect(t_ray *ray, t_parequation e, t_object *obj, int i);

/*
** sphere.c
*/
void		delete_sphere(t_sphere *sphere);
t_sphere	*new_sphere(t_objs_comp args, double rad);

/*
** triangle.c
*/
void		delete_triangle(t_triangle	*triangle);
t_triangle	*new_triangle(t_objs_comp args, t_dot dA, t_dot dB, t_dot dC);

#endif
