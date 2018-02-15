/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:52:29 by shiro             #+#    #+#             */
/*   Updated: 2018/02/15 16:14:07 by shiro            ###   ########.fr       */
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

int			parsing_material(char *data_mat, t_obj_material *material)
{
	char	*tmp[3];

	if ((tmp[0] = get_interval(data_mat, "<color>", "</color>")) && parsing_color(tmp[0], &material->color) == -1)
		return (-1);
	else if (!tmp[0])
		material->color = (SDL_Color){0, 0, 0, 255};
	material->chess = 0;
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

int	parsing_repeat(char *data, int *repeat)
{
	if (!ft_strequ(data, "true") && !ft_strequ(data, "false"))
		return (-1);
	*repeat = ft_strequ(data, "true");
	return (0);
}
