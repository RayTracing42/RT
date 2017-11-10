/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:14:48 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/10 13:24:36 by shiro            ###   ########.fr       */
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
	int			j;

	if (!(matrix = malloc(sizeof(t_matrix))))
		return (NULL);
	matrix->r = r;
	matrix->c = c;
	if (!mat)
	{
		if (!(matrix->mat = (double**)malloc(r * sizeof(double*))))
			return_free(NULL, matrix);
		i = -1;
		while (++i < r)
		{
			if (!(matrix->mat[i] = (double*)malloc(c * sizeof(double))))
				return_free(NULL, matrix);
			j = -1;
			while (++j < c)
				matrix->mat[i][j] = 0;
		}
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

t_matrix	*mult_matrix(t_matrix *m1, t_matrix *m2)
{
	t_matrix	*mult;
	int			r;
	int			c;
	int			i;

	if (m1->c != m2->r)
		return (NULL);
	mult = new_matrix(NULL, m1->r, m2->c);
	r = -1;
	while (++r < mult->r)
	{
		c = -1;
		while (++c < mult->c)
		{
			i = -1;
			mult->mat[r][c] = 0;
			while (++i < m1->c)
				mult->mat[r][c] += m1->mat[r][i] * m2->mat[i][c];
		}
	}
	return (mult);
}
