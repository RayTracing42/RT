/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2017/12/16 17:39:48 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_parequation	transform_equ(t_ray *ray, t_object *obj)
{
	t_parequation	trs;

	trs.vc = (t_vector){ray->equ.vc.x - obj->origin.x, ray->equ.vc.y - obj->origin.y, ray->equ.vc.z - obj->origin.z};
	mult_vect(&trs.vc, obj->trans_iconst, &trs.vc);
	mult_vect(&trs.vd, obj->trans_idir, &ray->equ.vd);
	return (trs);
}

void				transform_inter(t_ray *ray, t_object *obj)
{
	mult_vect(&ray->normal, obj->trans_norm, obj->get_normal(&ray->inter, obj));
	mult_vect((t_vector*)&ray->inter, obj->trans_const, (t_vector*)&ray->inter);
	ray->inter = (t_dot){ray->inter.x + obj->origin.x, ray->inter.y + obj->origin.y, ray->inter.z + obj->origin.z};
}

static double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		tmp;
	double		distance;
	int			nb;
	t_dot		inter;

	distance = 0;
	while (l_objs != NULL)
	{
		tmp = l_objs->obj->intersect(&ray->nb_intersect, &ray->inter, transform_equ(ray, l_objs->obj), l_objs->obj);
		if (gt(tmp, 0) && (eq(distance, 0) || (lt(tmp, distance) && gt(distance, 0))))
		{
			distance = tmp;
			transform_inter(ray, l_objs->obj);
			inter = ray->inter;
			ray->color = l_objs->obj->color;
			ray->obj = l_objs->obj;
			ray->percuted_refractive_i = l_objs->obj->obj_light.refractive_index;
			nb = ray->nb_intersect;
		}
		l_objs = l_objs->next;
	}
	ray->inter = inter;
	ray->nb_intersect = nb;
	return (distance);
}

SDL_Color		effects(t_ray *ray, t_scene *scn)
{
	SDL_Color	reflect_ray;
	SDL_Color	refract_ray;

	if (check_intersect(ray, scn->objects) > 0)
	{
		ray->color = shadows(ray, scn);
		reflect_ray = reflect(ray, scn);
		refract_ray = refract(ray, scn);
		get_reflected_col(ray, ray->obj, reflect_ray);
		get_refracted_col(ray, ray->obj, refract_ray);
		return (ray->color);
	}
	return (ray->color = (SDL_Color){0, 0, 0, 255});
}

void	scanning(t_scene *scn)
{
	int			x;
	int			y;
	t_ray		ray;

	ray.equ.vc = *(t_vector*)&scn->cam->origin;
	ray.actual_refractive_i = 1;
	ray.limit = 1;
	ray.tree = add_new_leaf(NULL, NULL, NULL, 0);
	printf("sphère 1 : %p | sphère 2 : %p\n", scn->objects->next->obj, scn->objects->next->next->obj);
	//y = 182;
	y = -1;
	//while (++y < 184)
	while (++y < WIN_HEIGHT)
	{
		//x = 599;
		x = -1;
		//while (++x < 601)
		while (++x < WIN_WIDTH)
		{
			printf("%d %d\n", x, y);
			view_plane_vector(x, y, scn->cam, &ray.equ.vd);
			effects(&ray, scn);
			put_pixel(x, y, &ray.color);
		}
	}
	remove_leaf(ray.tree);
}
