/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_objs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/19 14:41:24 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/08 04:52:04 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			new_cell_obj(t_list_objs **head, t_object *obj)
{
	t_list_objs	*tmp;

	if (!(tmp = malloc(sizeof(t_list_objs))))
		exit_error("rt", "malloc");
	tmp->obj = obj;
	tmp->next = *head;
	*head = tmp;
}

void			delete_cell_obj(t_list_objs **cell)
{
	t_list_objs	*tmp;

	tmp = *cell;
	*cell = (*cell)->next;
	free(tmp->obj);
	free(tmp);
}
