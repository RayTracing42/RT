/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:42 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/21 18:34:38 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H
# include "structures.h"

/*
** matrix.c
*/
void		clear_matrix(t_matrix *mat);
t_matrix	*create_identity(int i);
t_matrix	*new_matrix(double **mat, int r, int c);
void		delete_matrix(t_matrix *matrix);
t_matrix	*mult_matrix(t_matrix *m1, t_matrix *m2);

/*
** matrix_ops.c
*/
double		get_det_3x3mat(t_matrix *m);
t_matrix	*get_inv_3x3mat(t_matrix *res, t_matrix *m);
void		mult_vect(t_vector *dest, const t_matrix *mtx,
					const t_vector *vect);

/*
** transformations.c
*/
void		translation(t_matrix **mtx, double x, double y, double z);
void		x_rotation(t_matrix **mtx, double theta);
void		y_rotation(t_matrix **mtx, double theta);
void		z_rotation(t_matrix **mtx, double theta);
void		scale(t_matrix **mtx, double x, double y, double z);

#endif
