#ifndef SCANNING_H
# define SCANNING_H
# include "structures.h"

/*
**scanning.c
*/
SDL_Color		effects(t_ray *ray, t_scene *scn);
void			scanning(t_scene *scn);
t_parequation	transform_equ(t_ray *ray, t_object *obj);
void			transform_inter(t_ray *ray, t_object *obj);
void			valid_ray(t_ray *r1, double *t_r1, t_ray *r2, double *t_r2);

/*
** main.c
*/
int	main_display(void *scene);

#endif
