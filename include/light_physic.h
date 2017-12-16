/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_physic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 13:54:41 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/16 16:38:15 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_PHYSIC_H
# define LIGHT_PHYSIC_H
# include "structures.h"

t_vector	get_reflected_vect(const t_vector *dir, const t_vector *norm);
int			get_refracted_vect(t_vector *dir, const t_vector *norm, double n1, double n2);
void	get_reflected_col(t_ray *ray, t_object *src,
			SDL_Color reflected_obj_col);
void	get_refracted_col(t_ray *ray, t_object *src,
			SDL_Color refracted_obj_col);

#endif
