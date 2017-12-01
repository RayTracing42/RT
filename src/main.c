/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/25 22:51:11 by fcecilie         ###   ########.fr       */
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
		
		
		scn->objects->next->next->obj->local_limit.up_z = ft_memalloc(sizeof(double*));
		*scn->objects->next->next->obj->local_limit.up_z = -10;


		get_sdl_core();
		init_list_evts(&events, NULL);
		view_plane(scn->cam, scn->cam->vp);
		scanning(scn);
		refresh_win();
		wait_events(events);
		delete_sdl_core();
		exit(0);
	}
}
