/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/24 14:21:51 by shiro            ###   ########.fr       */
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

static int	main_display(void *scene)
{
	t_scene	*scn;

	scn = (t_scene*)scene;
	view_plane(scn->cam, scn->cam->vp);
	scanning(scn);
	refresh_win();
	delete_pxl_queues();
	return (1);
}

int			main(int ac, char **av)
{
	t_event		*events;
	t_scene		*scn;
	SDL_Thread	*t;

	events = NULL;
	if (!(scn = parsing(ac, av)))
		ft_putendl("usage : ./rt file.xml");
	else
	{
		if (DEBUG)
			ft_putstr("start ok\n");
		init_list_evts(&events, NULL);
		if (DEBUG)
			ft_putstr("init ok\n");
		t = SDL_CreateThread(main_display, "", scn);
		if (DEBUG)
			ft_putstr("thread instanced\n");
		// wait_events(events);
		if (DEBUG)
			ft_putstr("wait event\n");		
		SDL_WaitThread(t, NULL);
		if (DEBUG)
			ft_putstr("delete loading\n");
		delete_sdl_core();
		if (DEBUG)
			ft_putstr("delete ok\n");
	}
	exit(0);
}
