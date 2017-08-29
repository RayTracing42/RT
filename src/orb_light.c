/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orb_light.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 14:32:44 by edescoin          #+#    #+#             */
/*   Updated: 2017/08/25 15:06:10 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int	is_in_orb_light(void)
{
	return (1);
}

t_orb_light	*new_orb_light(t_dot orig, SDL_Color color)
{
	t_orb_light	*orb;

	orb = (t_orb_light*)new_spotlight((t_vector){0, 0, 0}, orig, color, 360);
	*(t_light_type*)&orb->type = ORB;
	orb->is_in_light = is_in_orb_light;
	return (orb);
}

void		delete_orb_light(t_orb_light *orb)
{
	delete_spotlight((t_spotlight*)orb);
}
