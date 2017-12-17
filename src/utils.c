/*============================================================================*/
/*                                                                            */
/*        fichier :   utils.c                                                 */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

double	angle_between_vectors(t_vector a, t_vector b)
{
	double	angle;
	double	pdt_scalaire;
	double	dist_a;
	double	dist_b;

	dist_a = sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2));
	dist_b = sqrt(pow(b.x, 2) + pow(b.y, 2) + pow(b.z, 2));
	if (!(dist_a && dist_b))
		return (0);
	pdt_scalaire = (a.x * b.x + a.y * b.y + a.z * b.z);
	angle = acos(pdt_scalaire / (dist_a * dist_b)) * 180 / M_PI;
	return (angle);
}

t_vector	vector_opposite(t_vector vec)
{
	return ((t_vector){-vec.x, -vec.y, -vec.z});
}

t_vector	vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_dot		dot(double x, double y, double z)
{
	t_dot	d;

	d.x = x;
	d.y = y;
	d.z = z;
	return (d);
}
