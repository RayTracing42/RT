/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mapping.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:17:00 by shiro             #+#    #+#             */
/*   Updated: 2018/02/12 15:04:58 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MAPPING_H
# define TEXTURE_MAPPING_H
# include "structures.h"

void	spherical_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture);
void	cylindrical_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture);
void	planar_mapping(t_dot i, t_dot *textel, double streching, SDL_Surface *texture);

#endif
