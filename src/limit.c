/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:57:03 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/17 10:24:51 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	normalized_diff(t_plane *p, t_dot *trans)
{
	double		dist;
	double		angle;
	t_vector	n;
	t_vector	o;

	o = (t_vector){p->orig_diff.x, p->orig_diff.y, p->orig_diff.z};
	if (!(o.x == 0 && o.y == 0 && o.z == 0))
	{
		n = p->normal;
		vect_normalize(&n);
		vect_normalize(&o);
		angle = angle_between_vectors(n, o);
		dist = get_vect_lenght(&p->orig_diff) * cos(angle * M_PI / 180);
		p->norm_diff = (t_vector){n.x * dist, n.y * dist, n.z * dist};
	}
	else
		p->norm_diff = (t_vector){0, 0, 0};
	trans->x += p->norm_diff.x;
	trans->y += p->norm_diff.y;
	trans->z += p->norm_diff.z;
}

int		empty_limit(t_ray *ray, t_ray *tmp_ray, t_object *father)
{
	t_plane *p;

	p = (t_plane *)tmp_ray->obj;
	if (local_limit_loop(tmp_ray, father))
	{
		transform_inter(tmp_ray, (t_object *)p);
		if (global_limit_loop(tmp_ray, father))
		{
			*ray = *tmp_ray;
			return (1);
		}
	}
	return (0);
}

int		full_limit(t_ray *ray, t_ray *tmp_ray, t_object *father)
{
	t_plane *p;

	p = (t_plane *)tmp_ray->obj;
	tmp_ray->inter.x += p->norm_diff.x;
	tmp_ray->inter.y += p->norm_diff.y;
	tmp_ray->inter.z += p->norm_diff.z;
	if (local_limit_loop(tmp_ray, father))
	{
		if (father->is_in_obj(&tmp_ray->inter, father))
		{
			transform_inter(tmp_ray, (t_object *)p);
			if (global_limit_loop(tmp_ray, father))
			{
				*ray = *tmp_ray;
				return (1);
			}
		}
	}
	return (0);
}
