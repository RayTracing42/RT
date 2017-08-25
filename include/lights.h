/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:04:49 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 15:01:10 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "structures.h"

t_light				*new_light(t_light_type type, t_vector direction,
								SDL_Color color);
t_spotlight			*new_spotlight(t_vector direction, t_dot orig,
								SDL_Color color, double aperture);
t_orb_light			*new_orb_light(t_dot orig, SDL_Color color);
t_parallel_light	*new_parallel_light(t_vector direction, SDL_Color color);

#endif /* end of include guard: LIGHT_H */
