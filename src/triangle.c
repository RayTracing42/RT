/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 17:16:14 by shiro             #+#    #+#             */
/*   Updated: 2017/12/11 17:47:18 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

static double			triangle_intersect(int *nbi, t_dot *dst, t_parequation e, t_object *obj)
{
		double		t;
		double		denom;
		t_triangle	*tgl;

		t = -1;
		*nbi = 0;
		tgl = (t_triangle*)obj;
		if (!(denom = tgl->a * e.vd.x + tgl->b * e.vd.y + tgl->c * e.vd.z))
			return (-1);
		t = -((tgl->a * e.vc.x + tgl->b * e.vc.y + tgl->c * e.vc.z + tgl->d) / denom);
		if (gt(t, 0))
		{
			*nbi = 1;
			*dst = equation_get_dot(&e, t);
		}
		return (t);
}

t_triangle	*new_triangle(t_objs_comp args, t_dot dA, t_dot dB, t_dot dC)
{
	t_triangle	*triangle;

	triangle = (t_triangle*)new_plane(args, vect_cross_product(dots_to_vect(dA, dB), dots_to_vect(dA, dC)), 1);
	triangle->dA = dA;
	triangle->dB = dB;
	triangle->dC = dC;
	return (triangle);
}

void		delete_triangle(t_triangle	*triangle)
{
	delete_plane((t_plane*)triangle);
}
