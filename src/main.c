/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/29 13:04:50 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		force_exit(void)
{
	exit(1);
	return (0);
}

void	init_list_evts(t_event **head, t_evt_data *data)
{
	new_event(head, SDL_KEYUP, data, &key_management);
	new_event(head, SDL_QUIT, NULL, &force_exit);
}

int		main(int ac, char **av)
{
	t_event		*events;

	(void)ac;
	(void)av;
	events = NULL;
	init_list_evts(&events, NULL);
	wait_events(events);
	delete_sdl_core();
	exit(0);
}
