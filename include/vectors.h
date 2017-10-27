/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:52:00 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/27 16:25:56 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "structures.h"

double		get_vect_lenght(const t_vector *vect);
double		vect_dot_product(const t_vector *v1, const t_vector *v2);
t_vector	vec_cross(t_vector a, t_vector b);
t_vector	vec_add(t_vector a, t_vector b);
t_vector	vec_sub(t_vector a, t_vector b);
t_vector	vec_prod(t_vector a, double i);
t_vector	norma(t_vector a);
double		scal(t_vector a, t_vector b);
double		scal_sqrd(t_vector a);
double		do_dist_sqrd(t_vector a, t_vector b);
double		do_dist(t_vector a);


#endif
