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

int		is_in_negative_obj(const double *t, const t_ray *ray, t_object *father)
{
	t_list_objs	*l;

	l = father->negative_obj;
	while (l)
	{
		if (ray->obj != l->obj)
			if (is_in_limited_obj(t, ray, l->obj))
				return (1);
		l = l->next;
	}
	return (0);
}

static void	list_is_not_in_negative_obj(t_list_ray **l_ray, t_couple_ray *neg)
{
	t_list_ray *l;

	l = *l_ray;
	while (l)
	{
		if (l->r.nb_intersect > 0 && lt(neg->ta, l->t) && lt(l->t, neg->tb))
			l->r.nb_intersect = 0;
		l = l->next;
	}
}

static void	valid_negative_points(t_list_ray **l_ray, t_couple_ray *neg, t_object *father)
{
	if (is_in_limited_obj(&neg->ta, &neg->a, father))
		if (!is_in_negative_obj(&neg->ta, &neg->a, father))
			add_cell_ray(l_ray, &neg->a, &neg->ta);
	if (is_in_limited_obj(&neg->tb, &neg->b, father))
		if (!is_in_negative_obj(&neg->tb, &neg->b, father))
			add_cell_ray(l_ray, &neg->b, &neg->tb);
}

void	negative_obj(t_list_ray **l_ray, t_couple_ray *basic, t_object *father, const t_ray *ray)
{
	t_couple_ray	neg;
	t_list_objs		*l;

	l = father->negative_obj;
	while (l)
	{
		neg.a = first_intersect(ray, l->obj, &neg.ta);
		neg.b = second_intersect(ray, l->obj, &neg.tb);
		if (neg.a.nb_intersect > 0 && neg.b.nb_intersect > 0)
		{
			transform_inter(&neg.a, l->obj);
			transform_inter(&neg.b, l->obj);
			if (l->obj->limit)
				limit3(&neg, l->obj, ray);
			if (neg.a.nb_intersect > 0 && neg.b.nb_intersect > 0)
			{
				list_is_not_in_negative_obj(l_ray, &neg);
				valid_negative_points(l_ray, &neg, father);
			}
			if (basic->a.nb_intersect > 0 && lt(neg.ta, basic->ta)
					&& lt(basic->ta, neg.tb))
				basic->a.nb_intersect = 0;
			if (basic->b.nb_intersect > 0 && lt(neg.ta, basic->tb)
					&& lt(basic->tb, neg.tb))
				basic->b.nb_intersect = 0;
		}
		l = l->next;
	}
}
