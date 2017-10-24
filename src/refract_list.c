/*============================================================================*/
/*                                                                            */
/*        fichier :   refract_list.c                                          */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

void	add_node(t_list_objs **l, t_object *obj)
{
	t_list_objs *new;

	if (!(new = ft_memalloc(sizeof(t_list_objs))))
		exit_error("rt", "malloc");
	new->next = NULL;
	new->obj = obj;
	if (l == NULL)
		*l = new;
	else
	{
		new->next = *l;
		*l = new;
	}
}

void	remove_node(t_list_objs **l, t_object *obj)
{
	t_list_objs *tmp;

	while (*l)
	{
		if ((*l)->obj == obj)
		{
			tmp = *l;
			*l = tmp->next;
			free(tmp);
		}
		else
			l = &(*l)->next;
	}
}

int		if_node_exist(t_list_objs *l, t_object *obj)
{
	t_list_objs *tmp;
	int			nb_node;

	tmp = l;
	nb_node = 0;
	while (tmp)
	{
		if (tmp->obj == obj)
			nb_node++;
		tmp = tmp->next;
	}
	return (nb_node);
}
