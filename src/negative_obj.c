/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   negative_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/04 03:59:05 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/26 14:24:33 by fcecilie         ###   ########.fr       */
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

int		negative_obj(t_couple_ray *basic, t_object *father, const t_ray *ray)
{
	t_couple_ray	neg;
	t_couple_ray	tmp;
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
				check[1] = limit(&tmp, l->obj, ray);
			if (check[1])
				valid_negative_points(&tmp, &neg, &check[0]);
		}
		l = (check[0]) ? father->negative_obj : l->next;
	}
	return (non_inverted_intersect(basic, &neg, 0));
}
