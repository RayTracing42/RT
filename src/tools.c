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

int		get_quad_equation_sol(double *res, double a, double b, double c)
{
	double	delta;
	double	s1;
	double	s2;

	if (!a)
	{
		if (!b)
			return (0);
		*res = -c / b;
		return (1);
	}
	if ((delta = (b * b) - (4 * a * c)) < 0)
		return (0);
	s1 = (-b - sqrt(delta)) / (2 * a),
	s2 = (-b + sqrt(delta)) / (2 * a);
	if (gt(s1, 0) && gt(s2, 0))
		*res = ft_dmin(s1, s2);
	else if (gt(s1, 0) || gt(s2, 0))
		*res = ft_dmax(s1, s2);
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
