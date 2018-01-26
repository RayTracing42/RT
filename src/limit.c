/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/22 10:27:56 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/26 14:25:47 by fcecilie         ###   ########.fr       */
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

static int		is_in_limit(const t_ray *ray, t_object *father)
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

static t_ray	empty_limit(const t_ray *ray, t_object *father, double *t_tmp,
	t_object *empty_limit, t_couple_ray *basic)
{
	t_ray	tmp;

	tmp = *ray;
	if (is_in_right_side_of_limit(basic->a.inter, empty_limit))
		tmp = first_intersect(ray, father, t_tmp);
	else if (is_in_right_side_of_limit(basic->b.inter, empty_limit))
		tmp = second_intersect(ray, father, t_tmp);
	else
		tmp.nb_intersect = 0;
	return (tmp);
}

int		limit(t_couple_ray *basic, t_object *father, const t_ray *ray)
{
	t_couple_ray	limited;
	t_list_objs		*l;
	t_ray			tmp;
	double			t_tmp;
	int				check_a;
	int				check_b;

	l = father->limit;
	limited = *basic;
	check_a = is_in_limit(&basic->a, father);
	check_b = is_in_limit(&basic->b, father);
	while (l)
	{
		tmp = (l->obj->status == FULL) ? first_intersect(ray, l->obj, &t_tmp) :
			empty_limit(ray, father, &t_tmp, l->obj, basic);
		if (tmp.nb_intersect > 0 && le(basic->ta, t_tmp) && le(t_tmp, basic->tb))
		{
			transform_inter(&tmp, l->obj);
			if (is_in_limit(&tmp, father))
			{
				if (!check_a && (t_tmp < limited.ta || limited.ta == basic->ta))
					valid_ray(&limited.a, &limited.ta, &tmp, &t_tmp);
				if (!check_b && (t_tmp > limited.tb || limited.tb == basic->tb))
					valid_ray(&limited.b, &limited.tb, &tmp, &t_tmp);
			}
		}
		l = l->next;
	}
	if ((!check_a && limited.ta == basic->ta)
		|| (!check_b && limited.tb == basic->tb))
		return (non_inverted_intersect(basic, &limited, 1));
	return (non_inverted_intersect(basic, &limited, 0));
}
