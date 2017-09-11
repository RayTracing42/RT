/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:45:00 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/11 12:51:40 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vector	*new_vector(double x, double y, double z)
{
	t_vector	*vect;

	if (!(vect = malloc(sizeof(t_dot))))
		return (NULL);
	vect->x = x;
	vect->y = y;
	vect->z = z;
	return (vect);
}

void		set_vector(t_vector *vect, double x, double y, double z)
{
	vect->x = x;
	vect->y = y;
	vect->z = z;
}

double		get_vect_lenght(const t_vector *vect)
{
	return (sqrt(pow(vect->x, 2) + pow(vect->y, 2) + pow(vect->z, 2)));
}

double		vect_dot_product(const t_vector *v1, const t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}
