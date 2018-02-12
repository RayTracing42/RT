/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:52:29 by shiro             #+#    #+#             */
/*   Updated: 2018/02/12 13:28:33 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "texture_mapping.h"

int			parsing_color(char *data_color, SDL_Color *c)
{
	char	*r;
	char	*g;
	char	*b;

	if (!(r = get_interval(data_color, "<r>", "</r>"))
			|| !(g = get_interval(data_color, "<g>", "</g>"))
			|| !(b = get_interval(data_color, "<b>", "</b>")))
		return (-1);
	*c = (SDL_Color){atoi(r), atoi(g), atoi(b), 255};
	free(r);
	free(g);
	free(b);
	return (0);
}

static int	parsing_mapping(char *mapping_method, t_obj_texture *txt_data)
{
	if (ft_strequ(mapping_method, "spherical"))
		txt_data->texture_mapping = spherical_mapping;
	else if (ft_strequ(mapping_method, "cylindrical"))
		txt_data->texture_mapping = cylindrical_mapping;
	else if (ft_strequ(mapping_method, "planar"))
		txt_data->texture_mapping = planar_mapping;
	else
		return (-1);
	return (0);
}

int			parsing_texture(char *data_txt, t_obj_texture *txt_data)
{
	char	*tmp[5];

	if ((tmp[0] = get_interval(data_txt, "<color>", "</color>")) && parsing_color(tmp[0], &txt_data->color) == -1)
		return (-1);
	txt_data->texture = NULL;
	if ((tmp[1] = get_interval(data_txt, "<file>", "</file>")))
	{
		if (!(txt_data->texture = SDL_LoadBMP(tmp[1])))
			exit_custom_error("rt: SDL2: SDL_LoadBMP: ", (char*)SDL_GetError());
		if (!(tmp[2] = get_interval(data_txt, "<scale>", "</scale>")))
			return (-1);
		if (!(txt_data->txt_streching = atod(tmp[2])))
			return (-1);
		if (!(tmp[3] = get_interval(data_txt, "<mapping>", "</mapping>")) || parsing_mapping(tmp[3], txt_data) == -1)
			return (-1);
		if (!(tmp[4] = get_interval(data_txt, "<transparency>", "</transparency>")) || parsing_color(tmp[4], &txt_data->transparent_color) == -1)
			txt_data->transparency = 0;
		else
			txt_data->transparency = 1;
		free(tmp[2]);
		free(tmp[3]);
	}
	else if (!tmp[0])
		return (-1);
	free(tmp[0]);
	free(tmp[1]);
	return (0);
}
