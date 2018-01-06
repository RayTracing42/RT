#ifndef GARBAGE_COLLECTOR_H
# define GARBAGE_COLLECTOR_H

# include <stdlib.h>
# include <unistd.h>

typedef struct			s_gb_cell
{
	void				*data;
	struct s_gb_cell	*next;
}						t_gb_cell;

#endif
