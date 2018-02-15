/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_textures2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 12:52:29 by shiro             #+#    #+#             */
/*   Updated: 2018/02/15 15:20:09 by shiro            ###   ########.fr       */
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
