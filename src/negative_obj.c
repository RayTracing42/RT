/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/31 05:46:57 by fcecilie         ###   ########.fr       */
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

int			is_in_negative_obj(const t_ray *ray, t_object *father, double *t,
	t_ray *unv)
{
	t_list_objs		*l;
	t_couple_ray	neg;
	t_couple_ray	lim;

	l = father->negative_obj;
	while (l)
	{
		if (unv->obj != l->obj)
		{
			lim.a.nb_intersect = 0;
			lim.b.nb_intersect = 0;
			neg.a = first_intersect(ray, l->obj, &neg.ta);
			neg.b = second_intersect(ray, l->obj, &neg.tb);
			if (neg.a.nb_intersect > 0 && neg.b.nb_intersect > 0)
			{
				if (l->obj->limit)
				{
					lim = limit(&neg, l->obj, ray);
					if (lim.a.nb_intersect == 0)
					{
						lim.a = neg.a;
						lim.ta = neg.ta;
					}
					if (lim.b.nb_intersect == 0)
					{
						lim.b = neg.b;
						lim.tb = neg.tb;
					}
					if (lim.a.nb_intersect > 0 && lim.b.nb_intersect > 0)
						if (le(lim.ta, *t))
							if (le(*t, lim.tb))
								return (1);
				}
				else
				{
					if (le(neg.ta, *t))
						if (le(*t, neg.tb))
							return (1);
				}
			}
		}
		l = l->next;
	}
	return (0);
}

void	unvalid_point_in_negative_obj(t_couple_ray *basic, t_object *father,
		t_ray *ray)
{
	if (father->negative_obj)
	{
		if (basic->a.nb_intersect > 0
			&& is_in_negative_obj(ray, father, &basic->ta, &basic->a))
			basic->a.nb_intersect = 0;
		if (basic->b.nb_intersect > 0
			&& is_in_negative_obj(ray, father, &basic->tb, &basic->b))
			basic->b.nb_intersect = 0;
	}
}

static void	valid_negative_points(t_couple_ray *tmp, t_couple_ray *neg, int *check)
{
	if ((*check = (lt(tmp->ta, neg->ta) && lt(neg->ta, tmp->tb))))
		valid_ray(&neg->a, &neg->ta, &tmp->b, &tmp->tb);
	if ((*check = (lt(tmp->ta, neg->tb) && lt(neg->tb, tmp->tb))))
		valid_ray(&neg->b, &neg->tb, &tmp->a, &tmp->ta);
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
	neg.a.nb_intersect = 0;
	neg.b.nb_intersect = 0;
	while (l)
	{
		check[0] = 0;
		tmp.a = first_intersect(ray, l->obj, &tmp.ta);
		tmp.b = second_intersect(ray, l->obj, &tmp.tb);
		if (tmp.a.nb_intersect > 0 && tmp.b.nb_intersect > 0)
		{
			transform_inter(&tmp.a, l->obj);
			transform_inter(&tmp.b, l->obj);
			if (l->obj->limit)
			{
				lim = limit(&tmp, l->obj, ray);
				tmp = lim;
			}
			if (tmp.a.nb_intersect > 0 && tmp.b.nb_intersect > 0)
				valid_negative_points(&tmp, &neg, &check[0]);
		}
		l = (check[0]) ? father->negative_obj : l->next;
	}
	return (neg);
}
