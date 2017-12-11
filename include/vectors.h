/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:52:00 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/11 17:37:51 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "structures.h"

t_vector	dots_to_vect(t_dot d1, t_dot d2);
double		get_vect_lenght(const t_vector *vect);
t_vector	vect_cross_product(const t_vector v1, const t_vector v2);
double		vect_dot_product(const t_vector *v1, const t_vector *v2);
void		vect_normalize(t_vector *v);

#endif
