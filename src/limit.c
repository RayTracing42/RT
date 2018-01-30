/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:27:56 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/30 05:57:17 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		is_in_right_side_of_limit(t_dot i, t_object *p)
{
	double	distance_1;
	double	distance_2;

	distance_1 = get_dot_dist(&i,
			&(t_dot){(p->origin.x + p->normal.x),
			(p->origin.y + p->normal.y),
			(p->origin.z + p->normal.z)});
	distance_2 = get_dot_dist(&i,
			&(t_dot){(p->origin.x - p->normal.x),
			(p->origin.y - p->normal.y),
			(p->origin.z - p->normal.z)});
	return ((distance_1 >= distance_2));
}

int				is_in_limit(const t_ray *ray, t_object *father)
{
	t_list_objs	*l;

	l = father->limit;
	while (l)
	{
		if (ray->obj != l->obj)
		{
			if (!is_in_right_side_of_limit(ray->inter, l->obj))
				return (0);
		}
		l = l->next;
	}
	return (1);
}

void	unvalid_point_in_limit(t_couple_ray *basic, t_object *father)
{
	if (father->limit)
	{
		if (!is_in_limit(&basic->a, father))
		{
			basic->ta = 0;
			basic->a.nb_intersect = 0;
		}
		if (!is_in_limit(&basic->b, father))
		{
			basic->tb = 0;
			basic->b.nb_intersect = 0;
		}
	}
}

void			a_b_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	if (couple->ta < *t_tmp && *t_tmp < couple->tb)
		valid_ray(&couple->b, &couple->tb, tmp, t_tmp);
	else if (*t_tmp < couple->ta && *t_tmp < couple->tb)
	{
		valid_ray(&couple->b, &couple->tb, &couple->a, &couple->ta);
		valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
	}
}

void			a_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	if (*t_tmp > couple->ta)
		valid_ray(&couple->b, &couple->tb, tmp, t_tmp);
	else
	{
		valid_ray(&couple->b, &couple->tb, &couple->a, &couple->ta);
		valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
	}
}

void			b_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	if (*t_tmp < couple->tb)
		valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
	else
	{
		valid_ray(&couple->a, &couple->ta, &couple->b, &couple->tb);
		valid_ray(&couple->b, &couple->tb, tmp, t_tmp);
	}
}

void			no_one_exist(t_couple_ray *couple, t_ray *tmp, double *t_tmp)
{
	valid_ray(&couple->a, &couple->ta, tmp, t_tmp);
}


t_couple_ray	limit(t_object *father, const t_ray *ray)
{
	t_couple_ray	limited;
	t_list_objs		*l;
	t_ray			tmp;
	double			t_tmp;

	l = father->limit;
	limited.a.nb_intersect = 0;
	limited.b.nb_intersect = 0;
	while (l)
	{
		tmp = first_intersect(ray, l->obj, &t_tmp);
		if (tmp.nb_intersect > 0)
		{
			transform_inter(&tmp, l->obj);
			if (is_in_limit(&tmp, father))
			{
				if (is_in_obj(t_tmp, tmp.inter, father))
				{
					if (limited.a.nb_intersect > 0 && limited.b.nb_intersect > 0)
						a_b_exist(&limited, &tmp, &t_tmp);
					else if (limited.a.nb_intersect > 0)
						a_exist(&limited, &tmp, &t_tmp);
					else if (limited.b.nb_intersect > 0)
						b_exist(&limited, &tmp, &t_tmp);
					else
						no_one_exist(&limited, &tmp, &t_tmp);
				}
			}
		}
		l = l->next;
	}
	return (limited);
}
