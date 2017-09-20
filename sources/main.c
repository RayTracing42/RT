/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 12:53:37 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/06 00:52:25 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int	force_exit(void)
{
	exit(1);
	return (0);
}
/*
static void	init_list_evts(t_event **head, t_evt_data *data)
{
	new_event(head, SDL_KEYUP, data, &key_management);
	new_event(head, SDL_QUIT, NULL, &force_exit);
}
*/
int			main(int ac, char **av)
{
//	t_event		*events;
	t_scene		*scn;

	if (!(scn = ft_memalloc(sizeof(t_scene))))
		return (0);
//	events = NULL;
//	get_sdl_core();
//	init_list_evts(&events, NULL);
	if (parsing(scn, ac, av[1]) == -1)
		return (-1);
	if (view_plane(scn->cam, scn->cam->vp) == -1)
		return (-1);
	printf("scn->cam->vp->up_left : (%.2f ; %.2f ; %.2f)\n", scn->cam->vp->up_left.x, scn->cam->vp->up_left.y, scn->cam->vp->up_left.z);
//	scanning();
//	display();
//	wait_events(events);
//	delete_sdl_core();
	exit(0);
}
