/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 01:23:38 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/30 05:28:49 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_cell_ray(t_list_ray **head, t_couple_ray *couple)
{
	t_list_ray	*tmp_a;
	t_list_ray	*tmp_b;

	if (couple->a.nb_intersect > 0 && gt(couple->ta, 0))
	{
		if (!(tmp_a = malloc(sizeof(t_list_ray))))
			exit_error("rt", "malloc");
		tmp_a->r = couple->a;
		tmp_a->t = couple->ta;
		tmp_a->next = *head;
		*head = tmp_a;
	}
	if (couple->b.nb_intersect > 0 && gt(couple->tb, 0))
	{
		if (!(tmp_b = malloc(sizeof(t_list_ray))))
			exit_error("rt", "malloc");
		tmp_b->r = couple->b;
		tmp_b->t = couple->tb;
		tmp_b->next = *head;
		*head = tmp_b;
	}
}

void			delete_cell_ray(t_list_ray **cell)
{
	t_list_ray	*tmp;

	tmp = *cell;
	*cell = (*cell)->next;
	free(tmp);
}
