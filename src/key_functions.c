/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/25 14:48:19 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/18 20:26:31 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	key_management(SDL_Event *current, t_event *evt)
{
	t_evt_data	*data;

	data = evt->data;
	if (current->key.keysym.sym == SDLK_ESCAPE)
		return (0);
	if (current->key.keysym.sym == SDLK_a && !get_sdl_core()->aa)
	{
		SDL_WaitThread(data->running_thread, NULL);
		get_sdl_core()->width *= 4;
		get_sdl_core()->height *= 4;
		SDL_DestroyTexture(get_sdl_core()->target);
		get_sdl_core()->target = SDL_CreateTexture(get_sdl_core()->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, WIN_WIDTH * 4, WIN_HEIGHT * 4);
		SDL_SetRenderTarget(get_sdl_core()->renderer, get_sdl_core()->target);
		get_sdl_core()->aa = 1;
		reset_camera(&data->scn->cam);
		data->running_thread = SDL_CreateThread(main_display, "", data->scn);
	}
	else if (current->key.keysym.sym == SDLK_s)
	{
		SDL_WaitThread(data->running_thread, NULL);
		screenshot();
	}
	return (1);
}
