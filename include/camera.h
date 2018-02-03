/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:29 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/03 14:12:43 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "structures.h"

/*
** camera.c
*/
t_camera	new_camera(const t_dot origin, const t_dot angle, double field_of_view, double depth_of_field);

#endif
