#include "garbage_collector.h"

static t_gb_cell	**get_list()
{
	static t_gb_cell *list = NULL;

	return (&list);
}

void		*galloc(size_t size)
{
	t_gb_cell	**list;
	t_gb_cell	*tmp;

	tmp = (t_gb_cell*)malloc(sizeof(t_gb_cell));
	tmp->data = malloc(size);
	tmp->next = *(list = get_list());
	*list = tmp;
	return (tmp->data);
}

void		gfree(void *ptr)
{
	t_gb_cell	**list;
	t_gb_cell	*tmp;

	list = get_list();
	if (!ptr)
		return ;
	while (*list)
	{
		if ((*list)->data == ptr)
		{
			tmp = *list;
			*list = tmp->next;
			free(tmp->data);
			free(tmp);
			return ;
		}
		else
			list = &(*list)->next;
	}
	write(2, "Warning: free():"
		" that pointer does not belong to you, leaks might occur\n", 72);
	free(ptr);
}

void		gexit(int status)
{
	t_gb_cell	**list;
	t_gb_cell	*tmp;

	if (status)
		exit(status);
	list = get_list();
	while (*list)
	{
		tmp = *list;
		*list = tmp->next;
		free(tmp->data);
		free(tmp);
	}
	exit(status);
}
