/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/20 20:50:52 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	force_exit(void)
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
	t_scene 	*scn;

	events = NULL;
	if (!(scn = parsing(ac, av)))
		ft_putendl("usage : ./rt file.xml");
	else
	{
		get_sdl_core();
		init_list_evts(&events, NULL);
		set_all_matrix(scn->objects->obj, (t_trans_data){(t_dot){5,5,5}, (t_dot){10,10,10}, (t_dot){1.2,1,1}});
		view_plane(scn->cam, scn->cam->vp);
		scanning(scn);
		refresh_win();
		wait_events(events);
		delete_sdl_core();
		exit(0);
	}
}
