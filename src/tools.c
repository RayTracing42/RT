/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:35:27 by edescoin          #+#    #+#             */
/*   Updated: 2017/11/29 04:06:40 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

int		gt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) > (long)(nb2 * POW));
}

int		lt(double nb1, double nb2)
{
	return ((long)(nb1 * POW) < (long)(nb2 * POW));
}

int		eq(double nb1, double nb2)
{
	return ((long)(nb1 * POW) == (long)(nb2 * POW));
}

int		get_quad_equation_sol(double *res, int i)
{
	double	delta;
	double	s1;
	double	s2;

	if (!res[1])
	{
		if (!res[2])
			return (0);
		res[0] = -res[3] / res[2];
		return (1);
	}
	if ((delta = (res[2] * res[2]) - (4 * res[1] * res[3])) < 0)
		return (0);
	s1 = (-res[2] - sqrt(delta)) / (2 * res[1]),
	s2 = (-res[2] + sqrt(delta)) / (2 * res[1]);
	if (gt(s1, 0) && gt(s2, 0))
		res[0] = (i == 1) ? ft_dmin(s1, s2) : ft_dmax(s1, s2);
	else if (gt(s1, 0) || gt(s2, 0))
		res[0] = (i == 2) ? ft_dmin(s1, s2) : ft_dmax(s1, s2);
	else
		return (0);
	return ((delta != 0) + 1);
}

t_dot	equation_get_dot(t_parequation *eq, double t)
{
	return ((t_dot){eq->vd.x * t + eq->vc.x,
					eq->vd.y * t + eq->vc.y,
					eq->vd.z * t + eq->vc.z});
}
