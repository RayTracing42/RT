/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_ops.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/04 16:30:54 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/28 14:32:46 by shiro            ###   ########.fr       */
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

t_matrix	*sub_matrix(t_matrix **res, t_matrix *m1, t_matrix *m2)
{
	int	i;
	int	j;

	if (!res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m1->r, m2->c);
	if (m1->r == m2->r && m1->c == m2->c)
	{
		i = -1;
		while (++i < m1->r)
		{
			j = -1;
			while (++j < m1->c)
				(*res)->mat[i][j] = m1->mat[i][j] - m2->mat[i][j];
		}
	}
	return (*res);
}

t_matrix	*add_matrix(t_matrix **res, t_matrix *m1, t_matrix *m2)
{
	int	i;
	int	j;

	if (!res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m1->r, m2->c);
	if (m1->r == m2->r && m1->c == m2->c)
	{
		i = -1;
		while (++i < m1->r)
		{
			j = -1;
			while (++j < m1->c)
				(*res)->mat[i][j] = m1->mat[i][j] + m2->mat[i][j];
		}
	}
	return (*res);
}

t_matrix	*get_inv_2x2mat(t_matrix **res, t_matrix *m)
{
	double			tmp[2][2];
	double			d;

	if (!res || !(d = (m->mat[0][0] * m->mat[1][1] - m->mat[0][1] * m->mat[1][0])))
		return (NULL);
	d = 1 / d;
	if (!*res)
		*res = new_matrix(NULL, m->r, m->c);
	tmp[0][0] = d * m->mat[1][1];
	tmp[0][1] = -d * m->mat[0][1];
	tmp[1][0] = -d * m->mat[1][0];
	tmp[1][1] = d * m->mat[0][0];
	(*res)->mat[0][0] = tmp[0][0];
	(*res)->mat[0][1] = tmp[0][1];
	(*res)->mat[1][0] = tmp[1][0];
	(*res)->mat[1][1] = tmp[1][1];
	return (*res);
}

static double	**set_2x2mat_tab(double **dst, t_matrix *m, int i, int j)
{
	if (!dst)
	{
		dst = (double**)malloc(2 * sizeof(double*));
		dst[0] = (double*)malloc(2 * sizeof(double));
		dst[1] = (double*)malloc(2 * sizeof(double));
	}
	if (i < m->r && (i + 1) < m->r && j < m->c && (j + 1) < m->c)
	{
		dst[0][0] = m->mat[i][j];
		dst[0][1] = m->mat[i][j + 1];
		dst[1][0] = m->mat[i + 1][j];
		dst[1][1] = m->mat[i + 1][j + 1];
	}
	return (dst);
}

static void	set_2x2tab_mat(t_matrix *dst, double **tab, int i, int j)
{
	if (i < dst->r && (i + 1) < dst->r && j < dst->c && (j + 1) < dst->c)
	{
		dst->mat[i][j] = tab[0][0];
		dst->mat[i][j + 1] = tab[0][1];
		dst->mat[i + 1][j] = tab[1][0];
		dst->mat[i + 1][j + 1] = tab[1][1];
	}
}

t_matrix	*neg_matrix(t_matrix **res, t_matrix *m)
{
	int	i;
	int	j;

	if (!res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m->r, m->c);
	i = -1;
	while (++i < m->r)
	{
		j = -1;
		while (++j < m->c)
			(*res)->mat[i][j] = -m->mat[i][j];
	}
	return (*res);
}

t_matrix	*get_inv_4x4mat(t_matrix *res, t_matrix *m)
{
	t_matrix		*abcd[4];
	t_matrix		*r_abcd[4];
	t_matrix		*invA;
	t_matrix		*invD;
	t_matrix		*comp1;
	t_matrix		*comp2;

	abcd[0] = new_matrix(set_2x2mat_tab(NULL, m, 0, 0), 2, 2);
	abcd[1] = new_matrix(set_2x2mat_tab(NULL, m, 0, 2), 2, 2);
	abcd[2] = new_matrix(set_2x2mat_tab(NULL, m, 2, 0), 2, 2);
	abcd[3] = new_matrix(set_2x2mat_tab(NULL, m, 2, 2), 2, 2);

	invA = NULL;
	invD = NULL;
	get_inv_2x2mat(&invA, abcd[0]);
	get_inv_2x2mat(&invD, abcd[3]);

	comp1 = NULL;
	comp2 = NULL;

	get_inv_2x2mat(&comp1, sub_matrix(&comp1, abcd[3], mult_matrix(&comp1, abcd[2], mult_matrix(&comp1, invA, abcd[1]))));
	get_inv_2x2mat(&comp2, sub_matrix(&comp2, abcd[0], mult_matrix(&comp2, abcd[1], mult_matrix(&comp2, invD, abcd[2]))));

	r_abcd[1] = NULL;
	r_abcd[2] = NULL;
	r_abcd[0] = comp2;
	neg_matrix(&r_abcd[1], mult_matrix(&r_abcd[1], invA, mult_matrix(&r_abcd[1], abcd[1], comp1)));
	neg_matrix(&r_abcd[2], mult_matrix(&r_abcd[2], comp1, mult_matrix(&r_abcd[2], abcd[2], invA)));
	r_abcd[3] = comp1;
	set_2x2tab_mat(res, r_abcd[0]->mat, 0, 0);
	set_2x2tab_mat(res, r_abcd[1]->mat, 0, 2);
	set_2x2tab_mat(res, r_abcd[2]->mat, 2, 0);
	set_2x2tab_mat(res, r_abcd[3]->mat, 2, 2);

	delete_matrix(abcd[0]);
	delete_matrix(abcd[1]);
	delete_matrix(abcd[2]);
	delete_matrix(abcd[3]);

	delete_matrix(r_abcd[0]);
	delete_matrix(r_abcd[1]);
	delete_matrix(r_abcd[2]);
	delete_matrix(r_abcd[3]);

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
