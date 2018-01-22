/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:45:00 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/18 12:56:12 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vector	dots_to_vect(t_dot d1, t_dot d2)
{
	return ((t_vector){d2.x - d1.x, d2.y - d1.y, d2.z - d1.z});
}

double		get_vect_lenght(const t_vector *vect)
{
	return (sqrt(pow(vect->x, 2) + pow(vect->y, 2) + pow(vect->z, 2)));
}

double		get_dot_dist(t_dot *d1, t_dot *d2)
{
	return (sqrt(pow(d2->x - d1->x, 2) + pow(d2->y - d1->y, 2) +
			pow(d2->z - d1->z, 2)));
}

double		vect_dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	vect_cross_product(const t_vector v1, const t_vector v2)
{
	return ((t_vector){v1.y * v2.z - v1.z * v2.y,
					v1.z * v2.x - v1.x * v2.z,
					v1.x * v2.y - v1.y * v2.x});
}

int			is_in_front_of_vector(t_dot dot, t_dot inter, t_vector normal)
{
	double	d1;
	double	d2;

	d1 = get_dot_dist(&dot, &(t_dot){inter.x + normal.x,
											inter.y + normal.y,
											inter.z + normal.z});
	d2 = get_dot_dist(&dot, &(t_dot){inter.x - normal.x,
											inter.y - normal.y,
											inter.z - normal.z});
	return (lt(d1, d2));
}
