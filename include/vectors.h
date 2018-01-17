/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:52:00 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/17 15:05:51 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "structures.h"

double	get_vect_lenght(const t_vector *vect);
double	vect_dot_product(const t_vector *v1, const t_vector *v2);
void	vect_normalize(t_vector *v);
int		is_in_front_of_vector(t_dot dot, t_dot inter, t_vector normal);

#endif
