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
	if (current->key.keysym.sym == SDLK_e)
	{
		refresh_win_effect(laplacian);
	}
	if (current->key.keysym.sym == SDLK_s)
	{
		gray();
		blur();
		blur();
		prewitt();
		negative();
		antia();
		antia();
		screenshot();
		refresh_win();
	}
	return (1);
}
