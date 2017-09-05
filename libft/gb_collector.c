/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gb_collector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 14:09:03 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/08 16:00:38 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	add_shit(t_garbage **pile, void *ptr, void (*fct)())
{
	t_garbage	*tmp;

	if ((tmp = malloc(sizeof(t_garbage))))
	{
		tmp->ptr = ptr;
		tmp->delete_ = fct;
		tmp->next = *pile;
		tmp->prev = NULL;
		if (*pile)
			(*pile)->prev = tmp;
		*pile = tmp;
	}
}

static void	remove_shit(t_garbage **pile, void *ptr)
{
	t_garbage	*tmp;

	tmp = *pile;
	if ((*pile)->ptr == ptr)
	{
		*pile = (*pile)->next;
		(*pile)->prev = NULL;
		free(tmp);
	}
	else
	{
		while (tmp && tmp->ptr != ptr)
			tmp = tmp->next;
		if (tmp)
		{
			tmp->prev->next = tmp->next;
			if (tmp->next)
				tmp->next->prev = tmp->prev;
			free(tmp);
		}
	}
}

static void	clear_all(t_garbage **pile)
{
	t_garbage	*tmp;

	while (*pile)
	{
		tmp = *pile;
		tmp->delete_(tmp->ptr);
		*pile = (*pile)->next;
		free(tmp);
	}
}

void		*garbage_collector(t_gbc_action action, void *ptr, void (*fct)())
{
	static t_garbage	*pile_of_shit = NULL;

	if (action == ADD && ptr && fct)
		add_shit(&pile_of_shit, ptr, fct);
	else if (action == REMOVE && ptr)
		remove_shit(&pile_of_shit, ptr);
	else if (action == CLEAR && pile_of_shit)
		clear_all(&pile_of_shit);
	return (ptr);
}
