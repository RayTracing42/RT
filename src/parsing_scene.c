/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 14:48:47 by fcecilie          #+#    #+#             */
/*   Updated: 2018/02/18 20:22:04 by edescoin         ###   ########.fr       */
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
static void	parsing_effects(char *data, t_scene *scn)
{
	int	i;
	char	*tmp;

	i = -1;
	while (*data && ft_isspace(*data))
		data++;
	tmp = NULL;
	while (tmp != data && *data)
	{
		tmp = data;
		data = parsing_anaglyph(data, scn, &i);
		data = parsing_blur(data, scn, &i);
		data = parsing_bwnoise(data, scn, &i);
		data = parsing_cartoon(data, scn, &i);
		data = parsing_duotone(data, scn, &i);
		data = parsing_gray(data, scn, &i);
		data = parsing_laplacian(data, scn, &i);
		data = parsing_lofi(data, scn, &i);
		data = parsing_motionblur(data, scn, &i);
		data = parsing_negative(data, scn, &i);
		data = parsing_noise(data, scn, &i);
		data = parsing_pop(data, scn, &i);
		data = parsing_prewitt(data, scn, &i);
		data = parsing_sepia(data, scn, &i);
	}
}

t_scene		*parsing_scene(char *scene)
{
	int			brightness;
	char		*data[3];
	t_scene		*scn;
	t_camera	cam;

	bg = NULL;
	if (parsing_camera(scene, &cam))
		exit_custom_error("rt", ":parsing_camera() failed");
	if (!(data[0] = get_interval(scene, "<brightness>", "</brightness>")))
		return (NULL);
	if (between(brightness = atod(data[0]), 0, 100) == -1)
		exit_custom_error("rt", ":brightness must be between <0 - 100>");
	if ((data[1] = get_interval(scene, "<background>", "</background>")))
		bg = parsing_background(data[1]);
	return (new_scene(cam, brightness, bg));
	scn = new_scene(cam, brightness);
	if ((data[2] = get_interval(scene, "<effects>", "</effects>")))
		parsing_effects(data, scn);
	free(data[0]);
	free(data[1]);
	free(data[2]);
	return (scn);
}
