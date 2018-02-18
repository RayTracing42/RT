/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:48:19 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 10:56:24 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			key_management(SDL_Event *current, t_event *evt)
{
	t_evt_data	*data;

	data = evt->data;
	if (current->key.keysym.sym == SDLK_ESCAPE)
		return (0);
	if (current->key.keysym.sym == SDLK_a)
		{
			if (get_sdl_core()->aa != 1)
			{
				SDL_WaitThread(data->running_thread, NULL);
				get_sdl_core()->width = (get_sdl_core()->width) * 4;
				get_sdl_core()->height = (get_sdl_core()->height) * 4;
				get_sdl_core()->aa = 2;
				reset_camera(&data->scn->cam);
				data->running_thread = SDL_CreateThread(main_display, "", data->scn);
			}
		}
	if (current->key.keysym.sym == SDLK_s)
		{
			SDL_WaitThread(data->running_thread, NULL);
			screenshot();
		}
	return (1);
}
