/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:41:24 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/05 03:20:24 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		new_cell_light(t_list_lights **head, t_light *light)
{
	t_list_lights	*tmp;

	if (!(tmp = malloc(sizeof(t_list_lights))))
		exit_error("rtv1", "malloc");
	tmp->light = light;
	tmp->next = *head;
	*head = tmp;
}

void		delete_cell_light(t_list_lights **cell)
{
	t_list_lights	*tmp;

	tmp = *cell;
	*cell = (*cell)->next;
	free(tmp->light);
	free(tmp);
}
