/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 13:54:41 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/03 15:52:33 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_SHADING_H
# define LIGHT_SHADING_H
# include "structures.h"

/*
**light_shading.c
*/
SDL_Color	get_shade_col(t_ray *light_ray, double opacity);
SDL_Color	get_specular_col(t_ray *ray, t_ray *light_ray, double opacity);

/*
**shadows.c
*/
SDL_Color	shadows(t_ray *ray, t_scene *scn);

#endif
