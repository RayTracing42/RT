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
		t_object *o;
		t_object *l;
		t_ray	ro;
		t_ray	rl;

		o = scn->objects->next->next->obj;
		l = (t_object*)scn->objects->next->next->obj->local_limit.p[0];

		ro.inter = o->origin;
		rl.inter = l->origin;
		printf("origin : (%.1f, %.1f, %.1f)\n", ro.inter.x, ro.inter.y, ro.inter.z);
		printf("origin : (%.1f, %.1f, %.1f)\n", rl.inter.x, rl.inter.y, rl.inter.z);
		mult_vect((t_vector*)&ro.inter, o->trans_const, (t_vector*)&ro.inter);
		mult_vect((t_vector*)&rl.inter, l->trans_const, (t_vector*)&rl.inter);
		printf("m_origin : (%.1f, %.1f, %.1f)\n", ro.inter.x, ro.inter.y, ro.inter.z);
		printf("m_origin : (%.1f, %.1f, %.1f)\n", rl.inter.x, rl.inter.y, rl.inter.z);



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
