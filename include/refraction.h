#ifndef REFRACTION_H
# define REFRACTION_H
# include "structures.h"

void		get_refracted_col(t_ray *ray, t_object *src,
							SDL_Color refracted_obj_col);
int			get_refracted_vect(t_vector *dir, const t_vector *norm, double n1,
								double n2);
SDL_Color	refract(t_ray *ray, t_scene *scn);

#endif
