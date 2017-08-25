/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 16:47:13 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 13:26:31 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H
# include "structures.h"

/*
** objects*.c
*/
void		delete_object(t_object *obj);
t_object	*new_object(t_type type, t_dot origin,
	 					t_vector dir, SDL_Color color);
void		set_object_color(t_object *obj, int r, int g, int b);
/*
void		rotate_object(t_object *obj, double x_angle, double y_angle,
						double z_angle);
void		scale_object(t_object *obj, double x, double y, double z);
void		translate_object(t_object *obj, double x, double y, double z);*/

/*
** box.c
*/
/*t_box		*new_box(t_dot fbl_corner, double x_width, double y_width,
					double z_width);*/

/*
** cone.c
*/
t_cone		*new_cone(t_objs_comp args, double angle, double height_top,
					double height_bottom);

/*
** cylinder.c
*/
t_cylinder	*new_cylinder(t_objs_comp args, double radius, double height_top,
						double height_bottom);

/*
** plane.c
*/
int			is_in_plane(t_dot *d, t_plane *p);
t_plane		*new_plane(t_objs_comp args, t_vector normal);

/*
** sphere.c
*/
t_sphere	*new_sphere(t_objs_comp args, double rad);

#endif
