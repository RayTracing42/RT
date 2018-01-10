/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/10 18:44:06 by shiro            ###   ########.fr       */
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
		//scene_add_object((t_object*)new_hyperboloid((t_objs_comp){(t_dot){50,0,0}, (SDL_Color){255,255,255,255},0,0,0,30}, 20, 20, 10, -1), scn);
		get_sdl_core();
		init_list_evts(&events, NULL);
		t = SDL_CreateThread(main_display, "", scn);
		wait_events(events);
		SDL_WaitThread(t, NULL);
		delete_sdl_core();
	}
	exit(0);
}
