/*============================================================================*/
/*                                                                            */
/*        fichier :   matrice_rotation.c                                      */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

/*
**	ATTENTION, ces matrices attendent un angle en radian /!\
*/

t_vector	matrice_rotation_x(t_vector *m, double angle)
{
	t_vector	vec;

	vec = vector(m->x * 1 + m->y * 0 + m->z * 0,
			m->x * 0 + m->y * cos(angle) - m->z * sin(angle),
			m->x * 0 + m->y * sin(angle) + m->z * cos(angle));
	return (vec);
}

t_vector	matrice_rotation_y(t_vector *m, double angle)
{
	t_vector	vec;

	vec = vector(m->x * cos(angle) + m->y * 0 + m->z * sin(angle),
			m->x * 0 + m->y * 1 + m->z * 0,
			-m->x * sin(angle) + m->y * 0 + m->z * cos(angle));
	return (vec);
}

t_vector	matrice_rotation_z(t_vector *m, double angle)
{
	t_vector	vec;
	
	vec = vector(m->x * cos(angle) - m->y * sin(angle) + m->z * 0,
			m->x * sin(angle) + m->y * cos(angle) + m->z * 0,
			m->x * 0 + m->y * 0 + m->z * 1);
	return (vec);
}
