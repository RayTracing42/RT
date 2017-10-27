/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 14:45:00 by edescoin          #+#    #+#             */
/*   Updated: 2017/10/27 16:26:01 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

t_vector	vec_cross(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.y * b.z - b.y * a.z;
	c.y = a.z * b.x - b.z * a.x;
	c.z = a.x * b.y - b.x * a.y;
	return (c);
}

t_vector	vec_add(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return (c);
}

t_vector	vec_sub(t_vector a, t_vector b)
{
	t_vector	c;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return (c);
}

t_vector	vec_prod(t_vector a, double i)
{
	t_vector	c;

	c.x = a.x * i;
	c.y = a.y * i;
	c.z = a.z * i;
	return (c);
}

t_vector	norma(t_vector a)
{
	double	dist;

	dist = do_dist(a);
	a.x = a.x / dist;
	a.y = a.y / dist;
	a.z = a.z / dist;
	return (a);
}
