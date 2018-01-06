/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 18:35:27 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/06 14:32:20 by shiro            ###   ########.fr       */
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

int		get_quad_equation_sol(double *res, double fac[3], int i)
{
	double	delta;
	double	s1;
	double	s2;

	if (!fac[_A])
	{
		if (!fac[_B])
			return (0);
		*res = -fac[_C] / fac[_B];
		return (1);
	}
	if ((delta = (fac[_B] * fac[_B]) - (4 * fac[_A] * fac[_C])) < 0)
		return (0);
	s1 = (-fac[_B] - sqrt(delta)) / (2 * fac[_A]);
	s2 = (-fac[_B] + sqrt(delta)) / (2 * fac[_A]);
	if (gt(s1, 0) && gt(s2, 0))
		*res = (i == 1) ? ft_dmin(s1, s2) : ft_dmax(s1, s2);
	else if (gt(s1, 0) || gt(s2, 0))
		*res = (i == 2) ? ft_dmin(s1, s2) : ft_dmax(s1, s2);
	else
		return (0);
	return (gt(s1, 0) + gt(s2, 0));
}

t_dot	equation_get_dot(t_parequation *eq, double t)
{
	return ((t_dot){eq->vd.x * t + eq->vc.x,
					eq->vd.y * t + eq->vc.y,
					eq->vd.z * t + eq->vc.z});
}
