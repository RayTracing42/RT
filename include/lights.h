/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:49 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/26 20:13:32 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "structures.h"

void				delete_light(t_light *light);
void				delete_orb_light(t_orb_light *orb);
void				delete_parallel_light(t_parallel_light *par);
void				delete_spotlight(t_spotlight *spot);

t_light				*new_light(t_light_type type, t_vector direction,
							SDL_Color color, double power);
t_spotlight	*new_spotlight(t_light_crd coords, SDL_Color color, double aperture,
						double power);
t_orb_light			*new_orb_light(t_dot orig, SDL_Color color, double power);
t_parallel_light	*new_parallel_light(t_vector direction, SDL_Color color,
										double power);

#endif
