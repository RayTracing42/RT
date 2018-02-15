/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 13:54:41 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/15 15:24:59 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_SHADING_H
# define LIGHT_SHADING_H
# include "structures.h"

/*
**light_shading.c
*/
SDL_Color	get_shade_col(t_ray *light_ray, double opacity, double *coef);
SDL_Color	get_specular_col(t_ray *ray, t_ray *light_ray, double opacity, int shade);

/*
**shadows.c
*/
int			check_objs_on_ray(t_ray *light_ray, t_list_objs *l_objs, t_light *light, t_object *filter);
SDL_Color	shadows(t_ray *ray, t_scene *scn);

#endif
