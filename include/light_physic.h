/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_physic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 13:54:41 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/12 13:49:50 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_PHYSIC_H
# define LIGHT_PHYSIC_H
# include "structures.h"

void	get_reflected_vect(t_vector *dir, const t_vector *norm);
void	get_refracted_vect(t_vector *dir, const t_vector *norm, t_object *src, t_object *dst);
void	get_reflected_col(t_ray *ray, t_object *src, SDL_Color reflected_obj_col);
void	get_refracted_col(t_ray *ray, t_object *src, SDL_Color refracted_obj_col);

#endif
