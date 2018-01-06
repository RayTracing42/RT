/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 13:04:14 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/22 13:05:01 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_OBJS_H
# define SCENE_OBJS_H
# include "structures.h"

void		delete_cell_obj(t_list_objs **cell);
void		scene_add_object(t_object *obj, t_scene *scene);
t_list_objs	*new_cell_obj(t_list_objs **head, t_object *obj);
#endif
