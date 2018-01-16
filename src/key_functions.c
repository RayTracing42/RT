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
	if (current->key.keysym.sym == SDLK_q)
		{
			refresh_win_effect(sepia);
		}
	if (current->key.keysym.sym == SDLK_w)
		{
			refresh_win_effect(gray);
		}
	if (current->key.keysym.sym == SDLK_e)
		{
			refresh_win_effect(antia);
		}
	if (current->key.keysym.sym == SDLK_r)
		{
			refresh_win_effect(blur);
		}
	if (current->key.keysym.sym == SDLK_t)
		{
			refresh_win_effect(negative);
		}
	if (current->key.keysym.sym == SDLK_y)
		{
			refresh_win_effect(anaglyph);
		}
	if (current->key.keysym.sym == SDLK_u)
		{
			refresh_win_effect(lofi);
		}
	if (current->key.keysym.sym == SDLK_i)
		{
			refresh_win();
		}
	if (current->key.keysym.sym == SDLK_s)
	{
		sepia();
		screenshot();
		refresh_win();
	}
	return (1);
}
