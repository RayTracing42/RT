/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:49 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/03 15:55:44 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "structures.h"

/*
**light.c
*/
void				delete_light(t_light *light);
t_light				*new_light(t_light_type type, t_vector direction, SDL_Color color, double power);

/*
**object_light.c
*/
void				delete_obj_light(t_obj_light *obl);
t_obj_light			*new_obj_light(double power, t_object *obj);

/*
**orb_light.c
*/
void				delete_orb_light(t_orb_light *orb);
t_orb_light			*new_orb_light(t_dot orig, SDL_Color color, double power);

/*
**parallel_light.c
*/
void				delete_parallel_light(t_parallel_light *par);
t_parallel_light	*new_parallel_light(t_vector direction, SDL_Color color, double power);

/*
**spotlight.c
*/
void				delete_spotlight(t_spotlight *spot);
t_spotlight			*new_spotlight(t_light_crd coords, SDL_Color color, double aperture, double power);

#endif
