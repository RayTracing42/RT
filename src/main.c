/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/12/21 12:44:27 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			force_exit(void)
{
	exit(1);
	return (0);
}

static void	init_list_evts(t_event **head, t_evt_data *data)
{
	new_event(head, SDL_KEYUP, data, &key_management);
	new_event(head, SDL_QUIT, NULL, &force_exit);
}


/*static int	fct_events(void* events)
{
	wait_events(events);
	return (1);
}*/

int			main(int ac, char **av)
{
	t_event		*events;
	t_scene		*scn;

//	SDL_Thread	*t;

	events = NULL;
	if (!(scn = parsing(ac, av)))
		ft_putendl("usage : ./rt file.xml");
	else
	{
		get_sdl_core();
		init_list_evts(&events, NULL);
//		t = SDL_CreateThread(fct_events, "events", events);
		view_plane(scn->cam, scn->cam->vp);
		scanning(scn);
		refresh_win();
//		SDL_WaitThread(t, NULL);
		wait_events(events);
		delete_sdl_core();
		exit(0);
	}
}
