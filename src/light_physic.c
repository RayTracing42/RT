/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_physic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:42:42 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/11 13:36:35 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

void	get_reflected_vect(t_vector *dir, const t_vector *norm)
{
	double	cos_theta1;

	cos_theta1 = vect_dot_product(norm, &(t_vector){-dir->x, -dir->y, -dir->z});
	dir->x += 2 * cos_theta1 * norm->x;
	dir->y += 2 * cos_theta1 * norm->y;
	dir->z += 2 * cos_theta1 * norm->z;
}

void	get_refracted_vect(t_vector *dir, const t_vector *norm,
						t_object *src, t_object *dst)
{
	double	cos_theta1;
	double	cos_theta2;
	double	n1_by_n2;

	cos_theta1 = vect_dot_product(norm, &(t_vector){-dir->x, -dir->y, -dir->z});
	n1_by_n2 = src->refraction / dst->refraction;
	cos_theta2 = sqrt(1 - pow(n1_by_n2, 2) * (1 - pow(cos_theta1, 2)));
	dir->x = n1_by_n2 * dir->x + (n1_by_n2 * cos_theta1 - cos_theta2) * norm->x;
	dir->y = n1_by_n2 * dir->y + (n1_by_n2 * cos_theta1 - cos_theta2) * norm->y;
	dir->z = n1_by_n2 * dir->z + (n1_by_n2 * cos_theta1 - cos_theta2) * norm->z;
}
