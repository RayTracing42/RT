/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/30 05:57:13 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
 **	check[0] verifie si on a modifie neg et donc si on doit reboucler pour
 **	verifier que les nouveaux points ne sont pas negativise par des objets
 **	deja teste precedement par la boucle -> recursif en iteratif;
 **
 **	check[1] verifie que la limitation de l'obj negatif s'est bien passe ou
 **	qu'il n'y a simplement pas eu de limite et que donc l'objet negatif est
 **	valide;
 */

static void	valid_negative_points(t_couple_ray *tmp, t_couple_ray *neg, int *check)
{
	if ((*check = (lt(tmp->ta, neg->ta) && lt(neg->ta, tmp->tb))))
		valid_ray(&neg->a, &neg->ta, &tmp->b, &tmp->tb);
	if ((*check = (lt(tmp->ta, neg->tb) && lt(neg->tb, tmp->tb))))
		valid_ray(&neg->b, &neg->tb, &tmp->a, &tmp->ta);
}

int	limit_negative_obj(t_couple_ray *tmp, t_couple_ray *lim, t_object *father)
{
	int		check_a;
	int		check_b;

	if (lim->a.nb_intersect > 0)
		valid_ray(&tmp->a, &tmp->ta, &lim->a, &lim->ta);
	if (lim->b.nb_intersect > 0)
		valid_ray(&tmp->b, &tmp->tb, &lim->b, &lim->tb);
	check_a = is_in_limit(&tmp->a, father);
	check_b = is_in_limit(&tmp->b, father);
	if (!check_a || !check_b)
		return (0);
	return (1);
}

int		is_in_negative_obj(double t, t_ray *ray, t_object *father)
{
	t_list_objs     *l;
	t_couple_ray	lim;

	l = father->negative_obj;
	while (l)
	{
		if (ray->obj != l->obj)
		{
			lim = limit(l->obj, ray);
			if (lim.a.nb_intersect > 0 && lim.b.nb_intersect > 0)
			{
				if (le(lim.ta, t) && le(t, lim.tb))
					return (1);
			}
		}
		l = l->next;
	}
	return (0);
}

void	unvalid_point_in_negative_obj(t_couple_ray *couple, t_object *father,
	t_ray *ray)
{
	if (father->negative_obj)
	{
		if (is_in_negative_obj(couple->ta, ray, father))
		{
			couple->ta = 0;
			couple->a.nb_intersect = 0;
		}
		if (is_in_negative_obj(couple->tb, ray, father))
		{
			couple->tb = 0;
			couple->b.nb_intersect = 0;
		}
	}
}

t_couple_ray	negative_obj(t_couple_ray *basic, t_object *father, const t_ray *ray)
{
	t_couple_ray	neg;
	t_couple_ray	tmp;
	t_couple_ray	lim;
	t_list_objs		*l;
	int				check[2];

	l = father->negative_obj;
	neg = *basic;
	while (l)
	{
		check[0] = 0;
		tmp.a = first_intersect(ray, l->obj, &tmp.ta);
		tmp.b = second_intersect(ray, l->obj, &tmp.tb);
		if (tmp.a.nb_intersect > 0 && tmp.b.nb_intersect > 0)
		{
			transform_inter(&tmp.a, l->obj);
			transform_inter(&tmp.b, l->obj);
			check[1] = 1;
			if (l->obj->limit)
			{
				lim = limit(l->obj, ray);
				check[1] = limit_negative_obj(&tmp, &lim, l->obj);
			}
			if (check[1])
				valid_negative_points(&tmp, &neg, &check[0]);
		}
		l = (check[0]) ? father->negative_obj : l->next;
	}
	return (neg);
}
