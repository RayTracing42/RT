/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 16:30:54 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/10 13:26:13 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

double		get_det_3x3mat(t_matrix *m)
{
	if (m->c < 3 || m->r < 3)
		return (0);
	return (m->mat[0][0] * m->mat[1][1] * m->mat[2][2] +
			m->mat[0][1] * m->mat[1][2] * m->mat[2][0] +
			m->mat[0][2] * m->mat[1][0] * m->mat[2][1] -
			m->mat[0][2] * m->mat[1][1] * m->mat[2][0] -
			m->mat[1][2] * m->mat[2][1] * m->mat[0][0] -
			m->mat[2][2] * m->mat[0][1] * m->mat[1][0]);
}

t_matrix	*get_inv_3x3mat(t_matrix *res, t_matrix *m)
{
	double			tmp[3][3];
	const double	d = get_det_3x3mat(m);
	int				i;
	int				j;

	if (!res)
		res = new_matrix(NULL, 3, 3);
	tmp[0][0] = (m->mat[1][1] * m->mat[2][2] - m->mat[1][2] * m->mat[2][1]) / d;
	tmp[0][1] = (m->mat[0][2] * m->mat[2][1] - m->mat[0][1] * m->mat[2][2]) / d;
	tmp[0][2] = (m->mat[0][1] * m->mat[1][2] - m->mat[0][2] * m->mat[1][1]) / d;
	tmp[1][0] = (m->mat[1][2] * m->mat[2][0] - m->mat[1][0] * m->mat[2][2]) / d;
	tmp[1][1] = (m->mat[0][0] * m->mat[2][2] - m->mat[0][2] * m->mat[2][0]) / d;
	tmp[1][2] = (m->mat[0][2] * m->mat[1][0] - m->mat[0][0] * m->mat[1][2]) / d;
	tmp[2][0] = (m->mat[1][0] * m->mat[2][1] - m->mat[1][1] * m->mat[2][0]) / d;
	tmp[2][1] = (m->mat[0][1] * m->mat[2][0] - m->mat[0][0] * m->mat[2][1]) / d;
	tmp[2][2] = (m->mat[0][0] * m->mat[1][1] - m->mat[0][1] * m->mat[1][0]) / d;
	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
			res->mat[i][j] = tmp[i][j];
	}
	return (res);
}

void		mult_vect(t_vector *dest, const t_matrix *mtx, const t_vector *vect)
{
	double	x;
	double	y;
	double	z;

	if (mtx->r >= 3 || mtx->c >= 4)
	{
		x = mtx->mat[0][0] * vect->x + mtx->mat[0][1] * vect->y +
				mtx->mat[0][2] * vect->z + mtx->mat[0][3];
		y = mtx->mat[1][0] * vect->x + mtx->mat[1][1] * vect->y +
				mtx->mat[1][2] * vect->z + mtx->mat[1][3];
		z = mtx->mat[2][0] * vect->x + mtx->mat[2][1] * vect->y +
				mtx->mat[2][2] * vect->z + mtx->mat[2][3];
		dest->x = x;
		dest->y = y;
		dest->z = z;
	}
}
