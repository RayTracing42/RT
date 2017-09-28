/*============================================================================*/
/*                                                                            */
/*        fichier :   vector_light.c                                          */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

t_vector	define_vector_orb(t_dot inter, t_orb_light *o)
{
	t_vector	vec;

	vec = vector(o->origin.x - inter.x, o->origin.y - inter.y, o->origin.z - inter.z);
	return (vec);
}

t_vector	define_vector_spot(t_dot inter, t_spotlight *s)
{
	t_vector	vec;

	vec = vector(s->origin.x - inter.x, s->origin.y - inter.y, s->origin.z - inter.z);
	return (vec);
}

t_vector	define_vector_parallel(t_parallel_light *p)
{
	t_vector	vec;

	vec = vector(-(p->direction.x), -(p->direction.y), -(p->direction.z));
	return (vec);
}
