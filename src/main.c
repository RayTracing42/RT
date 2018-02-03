/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/03 12:36:52 by shiro            ###   ########.fr       */
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

		//scene_add_light((t_light*)new_obj_light(1, (t_object*)new_sphere((t_objs_comp){(t_dot){0, 50, -10}, (SDL_Color){255, 255, 120, 255}, 0, 0, 0, 0}, 10)), scn);
		/*t_cone *c = new_cone((t_objs_comp){(t_dot){0, 20, -10}, (SDL_Color){255, 120, 255, 255}, 0, 0, 0, 0}, 10);
		c->upper = 1;
		scene_add_light((t_light*)new_obj_light(1, (t_object*)c), scn);

		c = new_cone((t_objs_comp){(t_dot){0, 20, -10}, (SDL_Color){255, 120, 255, 255}, 0, 0, 0, 0}, 10);
		c->upper = 0;
		scene_add_light((t_light*)new_obj_light(1, (t_object*)c), scn);*/
		//scene_add_light((t_light*)new_obj_light(1, (t_object*)new_cylinder((t_objs_comp){(t_dot){10, 20, -10}, (SDL_Color){120, 255, 255, 255}, 0, 0, 0, 0}, 5)), scn);
		//scene_add_light((t_light*)new_obj_light(1, (t_object*)new_plane((t_objs_comp){(t_dot){10, 20, 20}, (SDL_Color){255, 255, 255, 255}, 0, 0, 0, 0}, (t_vector){0, 0, -1}, 0)), scn);
		//scene_add_object(((t_obj_light*)scn->lights->light)->shape, scn);

		init_list_evts(&events, NULL);
		t = SDL_CreateThread(main_display, "", scn);
		wait_events(events);
		SDL_WaitThread(t, NULL);
		delete_sdl_core();
	}
	exit(0);
}
