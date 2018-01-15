/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:09:17 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/15 09:41:49 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int				is_in_boundaries(const t_plane *p, t_box *b, t_dot *d)
{
	if (p == b->front || p == b->back)
		return (d->z <= b->btr_corner.z && d->z >= b->fbl_corner.z &&
				d->y <= b->btr_corner.y && d->y >= b->fbl_corner.y);
	else if (p == b->top || p == b->bottom)
		return (d->x <= b->btr_corner.x && d->x >= b->fbl_corner.x &&
				d->z <= b->btr_corner.z && d->z >= b->fbl_corner.z);
	else if (p == b->left || p == b->right)
		return (d->y <= b->btr_corner.y && d->y >= b->fbl_corner.y &&
				d->x <= b->btr_corner.x && d->x >= b->fbl_corner.x);
	return (0);
}

static void				box_plane_intersect(t_ray *ray, const t_plane *p,
		t_parequation e, t_box_intersect *its)
{
	double		t;

	e = transform_equ(ray, (t_object *)p);
	if (gt(t = p->intersect(ray, e, (t_object*)p, 0), 0))
		if (is_in_boundaries(p, its->box, &ray->inter))
		{
			if (its->t == -1)
				ray->nb_intersect = 1;
			else
				ray->nb_intersect = 2;
			if (its->i == 1 && (lt(t, its->t) || its->t < 0))
			{
				its->p = (t_plane*)p;
				its->inter = ray->inter;
				its->t = t;
			}
			else if (its->i == 2 && gt(t, its->t))
			{
				its->p = (t_plane*)p;
				its->inter = ray->inter;
				its->t = t;
			}
		}
}

static double			box_intersect(t_ray *ray, t_parequation e, t_object *obj,
	int i)
{
	t_box_intersect	its;

	its = (t_box_intersect){(t_box*)obj, (t_dot){0, 0, 0}, i, -1, NULL};
	box_plane_intersect(ray, its.box->back, e, &its);
	box_plane_intersect(ray, its.box->front, e, &its);
	box_plane_intersect(ray, its.box->bottom, e, &its);
	box_plane_intersect(ray, its.box->top, e, &its);
	box_plane_intersect(ray, its.box->left, e, &its);
	box_plane_intersect(ray, its.box->right, e, &its);
	ray->inter = its.inter;
	ray->obj = (t_object *)its.p;
	return (its.t);
}

void					transform_plane(t_box *box, t_dot *size, t_trans_data *trs)
{
	t_dot	t;

	t = trs->trans;
	trs->trans = (t_dot){t.x - (size->x / 2), t.y, t.z};
	set_all_matrix((t_object *)box->front, *trs);
	trs->trans = (t_dot){t.x, t.y - (size->y / 2), t.z};
	set_all_matrix((t_object *)box->bottom, *trs);
	trs->trans = (t_dot){t.x, t.y, t.z - (size->z / 2)};
	set_all_matrix((t_object *)box->left, *trs);
	trs->trans = (t_dot){t.x + (size->x / 2), t.y, t.z};
	set_all_matrix((t_object *)box->back, *trs);
	trs->trans = (t_dot){t.x, t.y + (size->y / 2), t.z};
	set_all_matrix((t_object *)box->top, *trs);
	trs->trans = (t_dot){t.x, t.y, t.z + (size->z / 2)};
	set_all_matrix((t_object *)box->right, *trs);
	trs->trans = t;

}

t_box					*new_box(t_objs_comp args, t_dot *size, t_trans_data *trs)
{
	t_box	*box;

	box = (t_box*)new_object(BOX, args);
	box->fbl_corner = (t_dot){-(size->x / 2), -(size->y / 2), -(size->z / 2)};
	box->btr_corner = (t_dot){(size->x / 2), (size->y / 2), (size->z / 2)};
	box->front = new_plane(args, (t_vector){-1, 0, 0}, 0);
	box->bottom = new_plane(args, (t_vector){0, -1, 0}, 0);
	box->left = new_plane(args, (t_vector){0, 0, -1}, 0);
	box->back = new_plane(args, (t_vector){1, 0, 0}, 0);
	box->top = new_plane(args, (t_vector){0, 1, 0}, 0);
	box->right = new_plane(args, (t_vector){0, 0, 1}, 0);
	transform_plane(box, size, trs);
	box->intersect = &box_intersect;
	box->is_in_obj = NULL;
	box->get_normal = NULL;
	return (box);
}

void	delete_box(t_box *box)
{
	delete_plane(box->back);
	delete_plane(box->front);
	delete_plane(box->bottom);
	delete_plane(box->top);
	delete_plane(box->left);
	delete_plane(box->right);
	delete_object((t_object*)box);
}
