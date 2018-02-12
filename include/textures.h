/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 11:42:19 by shiro             #+#    #+#             */
/*   Updated: 2018/02/12 14:44:50 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H
# include "structures.h"

SDL_Color	getTextColor(t_dot pt, t_object *obj);
t_vector	getMapVector(t_dot pt, t_object *obj);

#endif
