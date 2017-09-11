/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:52:00 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/11 12:52:41 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "structures.h"

t_vector	*new_vector(double x, double y, double z);
void		set_vector(t_vector *vect, double x, double y, double z);
double		get_vect_lenght(const t_vector *vect);
double		vect_dot_product(const t_vector *v1, const t_vector *v2);

#endif
