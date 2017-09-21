/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:39 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 20:05:58 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "structures.h"

/*
** scene.c
*/
void		delete_scene(t_scene *scene);
t_scene		*new_scene(t_camera *cam, double brightness);
void		scene_add_object(t_object *obj, t_scene *scene);

#endif
