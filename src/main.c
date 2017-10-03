/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/29 14:35:49 by edescoin         ###   ########.fr       */
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

	(void)ac;
	(void)av;
	events = NULL;
	get_sdl_core();
	init_list_evts(&events, NULL);

	t_scene	*scn = new_scene(new_camera(60, (t_dot){-200, 30, 50}, 0, 0, 0), 75);
	scene_add_light((t_light*)new_orb_light((t_dot){200, 0, 0}, (SDL_Color){255, 255, 255, 255}), scn);
	scene_add_object((t_object*)new_sphere((t_objs_comp){(t_dot){200, 0, -50}, (t_vector){0, 0, 0}, (SDL_Color){100, 255, 120, 255}}, 40), scn);
	scene_add_object((t_object*)new_sphere((t_objs_comp){(t_dot){200, 0, 50}, (t_vector){0, 0, 0}, (SDL_Color){100, 80, 120, 255}}, 30), scn);
	scene_add_object((t_object*)new_plane((t_objs_comp){(t_dot){0, -50, 0}, (t_vector){0, 0, 0}, (SDL_Color){80, 120, 180, 255}}, (t_vector){0, 1, 0}), scn);

/*
	scene_add_object((t_object*)new_cone((t_objs_comp){(t_dot){200, 0, -100}, (t_vector){0, 0, 0}, (SDL_Color){100, 80, 120, 255}}, 20, 50, 30), scn);
	scene_add_object((t_object*)new_cylinder((t_objs_comp){(t_dot){200, 0, 0}, (t_vector){0, 0, 0}, (SDL_Color){120, 50, 70, 255}}, 20, 50, 30), scn);
*/

	view_plane(scn->cam, scn->cam->vp);
	scanning(scn);

	refresh_win();
	wait_events(events);
	delete_sdl_core();
	exit(0);
}
