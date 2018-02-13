#ifndef LIST_RAY_H
# define LIST_RAY_H
# include "structures.h"

void	add_cell_ray(t_list_ray **head, t_ray *ray, double *dist, int i);
void	delete_cell_ray(t_list_ray **cell);

#endif
