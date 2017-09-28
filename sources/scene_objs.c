/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:41:24 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/22 13:05:02 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_list_objs	*new_cell_obj(t_list_objs **head, t_object *obj)
{
	t_list_objs	*tmp;

	if (!(tmp = malloc(sizeof(t_list_objs))))
		exit_error("rtv1", "malloc");
	tmp->next = NULL;
	tmp->obj = obj;
	if (!head)
		return (tmp);
	tmp->next = *head;
	*head = tmp;
	return (tmp);
}

void				delete_cell_obj(t_list_objs **cell)
{
	t_list_objs	*tmp;

	tmp = *cell;
	*cell = (*cell)->next;
	free(tmp->obj);
	free(tmp);
}

void			scene_add_object(t_object *obj, t_scene *scene)
{
	if (!scene->objects)
		scene->objects = new_cell_obj(NULL, obj);
	else
		new_cell_obj(&scene->objects, obj);
}