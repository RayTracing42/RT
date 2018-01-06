/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refract_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 11:33:41 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/16 11:33:46 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	add_node(t_list_objs **l, t_object *obj)
{
	t_list_objs *new;

	if (!(new = ft_memalloc(sizeof(t_list_objs))))
		exit_error("rt", "malloc");
	new->next = NULL;
	new->obj = obj;
	if (*l == NULL)
		*l = new;
	else
	{
		new->next = *l;
		*l = new;
	}
}

void	remove_node(t_list_objs **l, t_object *obj)
{
	t_list_objs	*tmp;
	int			flag;

	flag = 0;
	while (*l && !flag)
	{
		if ((*l)->obj == obj)
		{
			tmp = *l;
			*l = tmp->next;
			free(tmp);
			flag = 1;
		}
		else
			l = &(*l)->next;
	}
}

int		if_node_exist(t_list_objs *l, t_object *obj)
{
	while (l && l->obj != obj)
		l = l->next;
	return (l && l->obj == obj);
}
