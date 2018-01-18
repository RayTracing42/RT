/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:14:48 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/08 03:24:56 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		clear_matrix(t_matrix *mat)
{
	int	i;
	int	j;

	i = -1;
	while (++i < mat->r)
	{
		j = -1;
		while (++j < mat->c)
			mat->mat[i][j] = 0;
	}
}

t_matrix	*new_matrix(double **mat, int r, int c)
{
	t_matrix	*matrix;
	int			i;

	if (!(matrix = malloc(sizeof(t_matrix))))
		return (NULL);
	matrix->r = r;
	matrix->c = c;
	if (!mat)
	{
		if (!(matrix->mat = (double**)malloc(r * sizeof(double*))))
			exit_error("rt", "malloc");
		i = -1;
		while (++i < r)
			if (!(matrix->mat[i] = (double*)malloc(c * sizeof(double))))
				exit_error("rt", "malloc");
		clear_matrix(matrix);
	}
	else
		matrix->mat = mat;
	return (matrix);
}

t_matrix	*create_identity(int i)
{
	t_matrix	*mtx;

	mtx = new_matrix(NULL, i, i);
	i = -1;
	while (++i < mtx->c)
		mtx->mat[i][i] = 1;
	return (mtx);
}

t_matrix	*copy_matrix(t_matrix *dst, t_matrix *src)
{
	int	i;
	int	j;

	if (dst->r != src->r || dst->c != src->c)
		return (NULL);
	i = -1;
	while (++i < dst->r)
	{
		j = -1;
		while (++j < dst->c)
			dst->mat[i][j] = src->mat[i][j];
	}
	return (dst);
}

void		delete_matrix(t_matrix *matrix)
{
	int	r;

	if (matrix)
	{
		r = -1;
		while (++r < matrix->r)
			free(matrix->mat[r]);
		free(matrix->mat);
		free(matrix);
	}
}

t_matrix	*mult_matrix(t_matrix **res, t_matrix *m1, t_matrix *m2)
{
	int			r;
	int			c;
	int			i;
	t_matrix	*tmp;

	if (m1->c != m2->r || !res)
		return (NULL);
	if (!*res)
		*res = new_matrix(NULL, m1->r, m2->c);
	tmp = new_matrix(NULL, m1->r, m2->c);
	r = -1;
	while (++r < (*res)->r)
	{
		c = -1;
		while (++c < (*res)->c)
		{
			i = -1;
			while (++i < m1->c)
				tmp->mat[r][c] += m1->mat[r][i] * m2->mat[i][c];
		}
	}
	copy_matrix(*res, tmp);
	delete_matrix(tmp);
	return (*res);
}
