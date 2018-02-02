/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_lights.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 13:04:14 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/22 13:11:32 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_LIGHTS_H
# define SCENE_LIGHTS_H
# include "structures.h"

void	delete_cell_light(t_list_lights **cell);
void	new_cell_light(t_list_lights **head, t_light *light);

#endif
