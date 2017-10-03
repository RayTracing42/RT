/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/12 16:32:56 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 11:49:22 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
void		rotate_object(t_object *obj, double x_angle, double y_angle,
						double z_angle)
{
	x_rotation(&obj->rot, x_angle);
	y_rotation(&obj->rot, y_angle);
	z_rotation(&obj->rot, z_angle);
	get_inv_3x3mat(obj->rot_inv, obj->rot);
}

void		translate_object(t_object *obj, double x, double y, double z)
{
	translation(&obj->trans, x, y, z);
	translation(&obj->trans_inv, -x, -y, -z);
}

void		scale_object(t_object *obj, double x, double y, double z)
{
	scale(&obj->scale, x, y, z);
	get_inv_3x3mat(obj->scale_inv, obj->scale);
}
*/
void		set_object_color(t_object *obj, int r, int g, int b)
{
	obj->color.r = r;
	obj->color.g = g;
	obj->color.b = b;
}
