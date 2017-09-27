/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:41:24 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/22 13:10:33 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_list_lights	*new_cell_light(t_list_lights **head, t_light *light)
{
	t_list_lights	*tmp;

	if (!(tmp = malloc(sizeof(t_list_lights))))
		exit_error("rtv1", "malloc");
	tmp->next = NULL;
	tmp->light = light;
	if (!head)
		return (tmp);
	tmp->next = *head;
	*head = tmp;
	return (tmp);
}

void					delete_cell_light(t_list_lights **cell)
{
	t_list_lights	*tmp;

	tmp = *cell;
	*cell = (*cell)->next;
	free(tmp->light);
	free(tmp);
}

void					scene_add_light(t_light *light, t_scene *scene)
{
	if (!scene->lights)
		scene->lights = new_cell_light(NULL, light);
	else
		new_cell_light(&scene->lights, light);
}
