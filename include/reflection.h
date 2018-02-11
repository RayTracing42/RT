#ifndef REFLECTION_H
# define REFLECTION_H
# include "structures.h"

void		get_reflected_col(t_ray *ray, t_object *src, SDL_Color reflected_obj_col);
t_vector	get_reflected_vect(const t_vector *dir, const t_vector *norm);
SDL_Color	reflect(t_ray *ray, t_scene *scn);

#endif
