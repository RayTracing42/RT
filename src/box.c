/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:09:17 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/08 21:03:28 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int				is_in_boundaries(t_plane *p, t_box *b, t_dot *d)
{
	if (p == b->front || p == b->back)
		return (d->x <= b->btr_corner.x && d->x >= b->fbl_corner.x &&
				d->y <= b->btr_corner.y && d->y >= b->fbl_corner.y);
	else if (p == b->top || p == b->bottom)
		return (d->x <= b->btr_corner.x && d->x >= b->fbl_corner.x &&
				d->z <= b->btr_corner.z && d->z >= b->fbl_corner.z);
	else if (p == b->left || p == b->right)
	{
		return (d->y <= b->btr_corner.y && d->y >= b->fbl_corner.y &&
				d->z <= b->btr_corner.z && d->z >= b->fbl_corner.z);
	}
	return (0);
}

static void				box_plane_intersect(t_ray *ray, t_plane *p,
										t_parequation e, t_box_intersect *its)
{
	double		t;

	if (gt(t = p->intersect(ray, e, (t_object*)p, 0), 0) &&
		is_in_boundaries(p, its->box, &ray->inter))
	{
		if (its->t == -1)
			ray->nb_intersect = 1;
		if (its->i == 1 && (lt(t, its->t) || lt(its->t, 0)))
			its->t = t;
		else if (its->i == 2 && gt(t, its->t))
			its->t = t;
	}
}

static double			box_intersect(t_ray *ray, t_parequation e, t_object *obj, int i)
{
	t_box_intersect	its;

	its = (t_box_intersect){(t_box*)obj, i, -1};
	box_plane_intersect(ray, its.box->front, e, &its);
	box_plane_intersect(ray, its.box->back, e, &its);
	box_plane_intersect(ray, its.box->bottom, e, &its);
	box_plane_intersect(ray, its.box->top, e, &its);
	box_plane_intersect(ray, its.box->left, e, &its);
	box_plane_intersect(ray, its.box->right, e, &its);
	return (its.t);
}

static const t_vector	*get_box_normal(t_dot *inter, t_object *obj)
{
	t_box	*b;

	b = (t_box*)obj;
	if (b->front->is_in_obj(inter, (t_object*)b->front))
		return (&b->front->normal);
	else if (b->back->is_in_obj(inter, (t_object*)b->back))
		return (&b->back->normal);
	else if (b->bottom->is_in_obj(inter, (t_object*)b->bottom))
		return (&b->bottom->normal);
	else if (b->top->is_in_obj(inter, (t_object*)b->top))
		return (&b->top->normal);
	else if (b->left->is_in_obj(inter, (t_object*)b->left))
		return (&b->left->normal);
	else
		return (&b->right->normal);
}

static int				is_in_box(t_dot *i, t_object *obj)
{
	t_box	*b;

	b = (t_box*)obj;
	if (b->front->is_in_obj(i, (t_object*)b->front))
		return (is_in_boundaries(b->front, b, i));
	else if (b->back->is_in_obj(i, (t_object*)b->back))
		return (is_in_boundaries(b->back, b, i));
	else if (b->bottom->is_in_obj(i, (t_object*)b->bottom))
		return (is_in_boundaries(b->bottom, b, i));
	else if (b->top->is_in_obj(i, (t_object*)b->top))
		return (is_in_boundaries(b->top, b, i));
	else if (b->left->is_in_obj(i, (t_object*)b->left))
		return (is_in_boundaries(b->left, b, i));
	else if (b->right->is_in_obj(i, (t_object*)b->right))
		return (is_in_boundaries(b->right, b, i));
	return (0);
}

t_box					*new_box(t_objs_comp args, double x_width,
								double y_width, double z_width)
{
	t_box	*box;

	box = (t_box*)new_object(BOX, args);
	box->fbl_corner = args.orig;
	box->btr_corner = (t_dot){args.orig.x + x_width, args.orig.y + y_width,
							args.orig.z + z_width};
	box->front = new_plane(args, (t_vector){-1, 0, 0}, 0);
	box->bottom = new_plane(args, (t_vector){0, -1, 0}, 0);
	box->left = new_plane(args, (t_vector){0, 0, -1}, 0);
	args.orig = box->btr_corner;
	box->back = new_plane(args, (t_vector){1, 0, 0}, 0);
	box->top = new_plane(args, (t_vector){0, 1, 0}, 0);
	box->right = new_plane(args, (t_vector){0, 0, 1}, 0);
	box->intersect = &box_intersect;
	box->get_normal = &get_box_normal;
	box->is_in_obj = &is_in_box;
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
