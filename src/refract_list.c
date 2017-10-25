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
	t_list_objs *prev;

	tmp = *l;
	prev = NULL;
	while (tmp)
	{
		if (tmp->obj == obj)
		{
			if (prev == NULL)
			{
				*l = tmp->next;
				free(tmp);
				tmp = *l;
			}
			else
			{
				prev->next = tmp->next;
				free(tmp);
				tmp = prev;
			}
		}
		if (tmp)
		{	
			prev = tmp;
			tmp = tmp->next;
		}
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
