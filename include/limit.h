#ifndef LIMIT_H
# define LIMIT_H
# include "structures.h"

void	limit(t_couple_ray *basic, t_object *father, const t_ray *ray);
void	limit2(t_couple_ray *limited, t_ray *tmp, double *t_tmp);
int		is_in_limit(const t_ray *ray, t_object *father);

#endif
