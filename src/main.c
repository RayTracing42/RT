/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 15:31:17 by edescoin         ###   ########.fr       */
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
	scene_add_light((t_light*)new_spotlight((t_vector){0,0,0}, (t_dot){0,0,0}, (SDL_Color){0,0,0,0}, 360), sc);
	wait_events(events);
	delete_sdl_core();
	exit(0);
}
