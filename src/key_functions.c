/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:48:19 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 14:41:44 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			key_management(SDL_Event *current, t_event *evt)
{
	t_evt_data	*data;

	data = evt->data;
	(void)data;
	if (current->key.keysym.sym == SDLK_ESCAPE)
		return (0);
	if (current->key.keysym.sym == SDLK_a)
		{
			get_sdl_core()->width = (get_sdl_core()->width) * 2;
			get_sdl_core()->height = (get_sdl_core()->height) * 2;
			get_sdl_core()->aa = 10;
		}
	if (current->key.keysym.sym == SDLK_s)
		{
			screenshot();
		}
	if (current->key.keysym.sym == SDLK_d)
		{
			antia();
			refresh_win();
		}
	return (1);
}
