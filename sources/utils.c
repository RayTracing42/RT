/*============================================================================*/
/*                                                                            */
/*        fichier :   utils.c                                                 */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

double	delta(double a, double b, double c)
{
	double	d;
	double	r1;
	double	r2;

	d = (b * b) - (4 * a * c);
	if (d < 0)
		return (0);
	r1 = ((b * -1) + sqrt(d)) / (2 * a);
	if (d == 0)
		return (r1);
	r2 = ((b * -1) - sqrt(d)) / (2 * a);
	if (r1 < r2)
		return (r1);
	else
		return (r2);
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
