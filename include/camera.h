/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:29 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 20:13:36 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "structures.h"

/*
** camera.c
*/
void		delete_camera(t_camera *cam);
//void		init_cam_screen(t_camera *cam);
t_camera	*new_camera(int fov, const t_dot origin,
						double angle_x, double angle_y, double angle_z);
t_camera	*parsing_camera(char *file);

#endif
