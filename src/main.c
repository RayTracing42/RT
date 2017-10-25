/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 14:40:48 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	force_exit(void)
{
	exit(1);
	return (0);
}

static void	init_list_evts(t_event **head, t_evt_data *data)
{
	new_event(head, SDL_KEYUP, data, &key_management);
	new_event(head, SDL_QUIT, NULL, &force_exit);
}

int			main(int ac, char **av)
{
	t_event		*events;

	(void)ac;
	(void)av;
	events = NULL;
	get_sdl_core();
	init_list_evts(&events, NULL);
	t_scene *sc = new_scene(NULL, 50);
	scene_add_light((t_light*)new_orb_light((t_dot){0,0,0}, (SDL_Color){0,0,0,0}), sc);
	wait_events(events);
	delete_sdl_core();
	exit(0);
}
