/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:41:24 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/22 13:13:31 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_scene	*new_scene(t_camera *cam, double brightness)
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

void	delete_scene(t_scene *scene)
{
	if (scene)
	{
		while (scene->objects)
			delete_cell_obj(&scene->objects);
		delete_camera(scene->cam);
		free(scene);
	}
}
