/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:41:24 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/21 20:42:45 by edescoin         ###   ########.fr       */
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

static void		delete_cell_obj(t_list_objs **cell)
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

void			delete_scene(t_scene *scene)
{
	if (scene)
	{
		while (scene->objects)
			delete_cell_obj(&scene->objects);
		delete_camera(scene->cam);
		//delete_spotlight(scene->light);
		free(scene);
	}
}

t_scene			*new_scene(t_camera *cam, double brightness)
{
	t_scene	*scene;

	if (!(scene = malloc(sizeof(t_scene))))
		exit_error("rtv1", "malloc");
	if (brightness > 100)
		brightness = 100;
	if (brightness < 0)
		brightness = 0;
	scene->brightness = brightness / 100;
	scene->cam = cam;
	scene->lights = NULL;
	scene->objects = NULL;
	return (scene);
}
