/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 12:52:00 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/11 17:11:03 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H
# include "structures.h"

double	get_vect_lenght(const t_vector *vect);
double	vect_dot_product(const t_vector *v1, const t_vector *v2);
void	vect_normalize(t_vector *v);

#endif
