/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/25 17:03:10 by edescoin         ###   ########.fr       */
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
	printf("1\n");
	get_sdl_core();
	printf("2\n");
	init_list_evts(&events, NULL);
	printf("3\n");

	t_scene	*scn = new_scene(new_camera(60, (t_dot){-100, 20, 0}, 0, 0, 0), 75);
	scene_add_light((t_light*)new_orb_light((t_dot){200, -200, 0}, (SDL_Color){255, 255, 255, 255}), scn);
	scene_add_light((t_light*)new_orb_light((t_dot){0, 200, 0}, (SDL_Color){255, 255, 255, 255}), scn);
	scene_add_light((t_light*)new_orb_light((t_dot){0, -200, 0}, (SDL_Color){255, 255, 255, 255}), scn);
	scene_add_light((t_light*)new_orb_light((t_dot){200, 200, 0}, (SDL_Color){255, 255, 255, 255}), scn);
	scene_add_object((t_object*)new_sphere((t_objs_comp){(t_dot){400, 20, -30}, (t_vector){0, 0, 0}, (SDL_Color){255, 255, 0, 255}, 0, 0, 1.5}, 40), scn);
	scene_add_object((t_object*)new_sphere((t_objs_comp){(t_dot){400, 20, 30}, (t_vector){0, 0, 0}, (SDL_Color){255, 0, 255, 255}, 0, 0, 1.5}, 40), scn);
	scene_add_object((t_object*)new_sphere((t_objs_comp){(t_dot){100, 20, 0}, (t_vector){0, 0, 0}, (SDL_Color){255, 0, 0, 255}, 0, 0.7, 1.5}, 20), scn);
	scene_add_object((t_object*)new_cylinder((t_objs_comp){(t_dot){100, 20, 0}, (t_vector){0, 0, 0}, (SDL_Color){0, 0, 255, 255}, 0, 0.7, 1.8}, 5, 5, 5), scn);

	printf("4\n");
	view_plane(scn->cam, scn->cam->vp);
	printf("5\n");
	scanning(scn);
	printf("6\n");
	refresh_win();
	printf("7\n");
	wait_events(events);
	printf("8\n");
	delete_sdl_core();
	printf("9\n");
	exit(0);
}
