/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_shading.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 13:54:41 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/26 20:19:41 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_SHADING_H
# define LIGHT_SHADING_H
# include "structures.h"

SDL_Color	get_shade_col(t_ray *ray, const t_scene *scene);

#endif
