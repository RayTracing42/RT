/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:33 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/05 23:50:03 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H
# include "structures.h"
# include "key_functions.h"
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include <SDL2/SDL.h>
# endif

/*
** events.c
*/
void	clear_events(t_event **head);
void	delete_event(t_event **head);
void	new_event(t_event **head, SDL_EventType type, void *data, int (*fct)());
void	wait_events(t_event *list_evts, t_scene *scn);

#endif
