/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:48:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/17 16:45:51 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static SDL_Texture	*parsing_background(char *file)
{
	SDL_Surface	*tmp;
	SDL_Texture	*bg;

	if (!(tmp = SDL_LoadBMP(file)))
		exit_custom_error("rt: SDL2: SDL_LoadBMP: ", (char*)SDL_GetError());
	if (!(bg = SDL_CreateTextureFromSurface(get_sdl_core()->renderer, tmp)))
		exit_custom_error("rt: SDL2: SDL_CreateTextureFromSurface: ",
						(char*)SDL_GetError());
	SDL_FreeSurface(tmp);
	return (bg);
}

t_scene				*parsing_scene(char *scene)
{
	char		*data[2];
	t_camera	cam;
	int			brightness;
	SDL_Texture	*bg;

	bg = NULL;
	if (parsing_camera(scene, &cam))
		exit_custom_error("rt", ":parsing_camera() failed");
	if (!(data[0] = get_interval(scene, "<brightness>", "</brightness>")))
		return (NULL);
	if (between(brightness = atod(data[0]), 0, 100) == -1)
		exit_custom_error("rt", ":brightness must be between <0 - 100>");
	if ((data[1] = get_interval(scene, "<background>", "</background>")))
		bg = parsing_background(data[1]);
	free(data[0]);
	free(data[1]);
	return (new_scene(cam, brightness, bg));
}
