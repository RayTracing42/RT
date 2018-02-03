/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:39 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/03 14:14:53 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "structures.h"
# include "scene_objs.h"
# include "scene_lights.h"

/*
** scene.c
*/
void		delete_scene(t_scene *scene);
t_scene		*new_scene(t_camera cam, double brightness);
t_scene		*parsing_scene(char *file);

#endif
