/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:52:29 by shiro             #+#    #+#             */
/*   Updated: 2018/02/14 14:43:42 by shiro            ###   ########.fr       */
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

static int	parsing_mapping(char *mapping_method, void (**fct)(t_dot i, t_dot *textel, double streching, SDL_Surface *texture))
{
	if (ft_strequ(mapping_method, "spherical"))
		*fct = spherical_mapping;
	else if (ft_strequ(mapping_method, "cylindrical"))
		*fct = cylindrical_mapping;
	else if (ft_strequ(mapping_method, "planar"))
		*fct = planar_mapping;
	else
		return (-1);
	return (0);
}

static int	parsing_texture(char *data_txt, t_obj_material *material)
{
	char	*tmp[4];

	if (!(tmp[0] = get_interval(data_txt, "<file>", "</file>")))
		return (-1);
	if (ft_strequ(tmp[0], "chess"))
		material->chess = 1;
	else if (!(material->texture = SDL_LoadBMP(tmp[0])))
		exit_custom_error("rt: SDL2: SDL_LoadBMP: ", (char*)SDL_GetError());
	if (!(tmp[1] = get_interval(data_txt, "<scale>", "</scale>")))
		return (-1);
	if (!(material->txt_streching = atod(tmp[1])))
		return (-1);
	if (!(tmp[2] = get_interval(data_txt, "<mapping>", "</mapping>")) || parsing_mapping(tmp[2], &material->texture_mapping) == -1)
		return (-1);
	if (!(tmp[3] = get_interval(data_txt, "<transparency>", "</transparency>")) || parsing_color(tmp[3], &material->transparent_color) == -1)
		material->transparency = 0;
	else
		material->transparency = 1;
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	free(tmp[3]);
	return (0);
}

static int	parsing_normal_map(char *data_map, t_obj_material *material)
{
	char	*tmp[3];

	if (!(tmp[0] = get_interval(data_map, "<file>", "</file>")))
		return (-1);
	if (!(material->normal_map = SDL_LoadBMP(tmp[0])))
		exit_custom_error("rt: SDL2: SDL_LoadBMP: ", (char*)SDL_GetError());
	if (!(tmp[1] = get_interval(data_map, "<scale>", "</scale>")) && !material->texture)
		return (-1);
	else if (!tmp[1] && material->texture)
			material->map_streching = material->txt_streching;
	else if (!(material->map_streching = atod(tmp[1])))
		return (-1);
	if (!(tmp[2] = get_interval(data_map, "<mapping>", "</mapping>")) && !material->texture)
		return (-1);
	else if (!tmp[2] && material->texture)
		material->map_mapping = material->texture_mapping;
	else if (parsing_mapping(tmp[2], &material->map_mapping) == -1)
		return (-1);
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	return (0);
}

int			parsing_material(char *data_mat, t_obj_material *material)
{
	char	*tmp[3];

	if ((tmp[0] = get_interval(data_mat, "<color>", "</color>")) && parsing_color(tmp[0], &material->color) == -1)
		return (-1);
	else if (!tmp[0])
		material->color = (SDL_Color){0, 0, 0, 0};
	material->texture = NULL;
	if ((tmp[1] = get_interval(data_mat, "<texture>", "</texture>")) && parsing_texture(tmp[1], material) == -1 && !tmp[0])
		return (-1);
	material->normal_map = NULL;
	if ((tmp[2] = get_interval(data_mat, "<normal_map>", "</normal_map>")) && parsing_normal_map(tmp[2], material) == -1)
	free(tmp[0]);
	free(tmp[1]);
	free(tmp[2]);
	return (0);
}
