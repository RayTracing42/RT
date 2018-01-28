/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aancel <aancel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 03:10:18 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/26 20:16:36 by aancel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double	check_intersect(t_ray *ray, t_list_objs *l_objs)
{
	double		dist;
	double		tmp;
	t_ray		tmp_ray;

	dist = 0;
	tmp_ray.shad_opacity = 0;
	while (l_objs != NULL)
	{
		tmp_ray = first_intersect(ray, l_objs->obj, &tmp);
		if (gt(tmp, 0) && (eq(dist, 0) || (lt(tmp, dist) && gt(dist, 0))))
		{
			transform_inter(&tmp_ray, tmp_ray.obj);
			if (is_in_limit(&tmp_ray, l_objs->obj))
			{
				dist = tmp;
				*ray = tmp_ray;
			}
			else
				check_limit_intersect(ray, l_objs->obj, &dist);
		}
		l_objs = l_objs->next;
	}
	return (dist);
}

Uint32 GetPixel32(SDL_Surface* image,int i,int j)
{
    if (i<0 || i>image->w-1 || j<0 || j>image->h-1)
        return 0;
    return ((Uint32*)(image->pixels))[j*(image->pitch/4)+i];
}

SDL_Color getTextColor(t_parequation e, double t, t_object *obj)
{
	t_dot pt;

	pt.x = e.vc.x + e.vd.x * t;
	pt.y = e.vc.y + e.vd.y * t;
	pt.z = e.vc.z + e.vd.z * t;

	pt.x = (int)pt.x % (int)e->text->x;
	pt.y = (int)pt.y % (int)e->text->y;

}

t_ray	first_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;
	t_parequation e;

	tmp_ray = *ray;
	e = transform_equ(&tmp_ray, obj);
	*tmp = obj->intersect(&tmp_ray, e, obj, 1);
	tmp_ray.normal = obj->get_normal(&tmp_ray.inter, obj);
	//SDL_LockMutex(get_mutexes()->intersect);
	tmp_ray.color = obj->color;
	tmp_ray.color = getTextColor(e, *tmp, obj)
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	//SDL_UnlockMutex(get_mutexes()->intersect);
	if (gt(*tmp, 0))
		tmp_ray.shad_opacity += (1 - tmp_ray.obj->obj_light.refraction_amount);
	return (tmp_ray);
}

t_ray	second_intersect(const t_ray *ray, t_object *obj, double *tmp)
{
	t_ray	tmp_ray;

	tmp_ray = *ray;
	*tmp = obj->intersect(&tmp_ray, transform_equ(&tmp_ray, obj), obj, 2);
	tmp_ray.normal = obj->get_normal(&tmp_ray.inter, obj);
	//SDL_LockMutex(get_mutexes()->intersect);
	tmp_ray.color = obj->color;
	tmp_ray.percuted_refractive_i = obj->obj_light.refractive_index;
	tmp_ray.obj = obj;
	//SDL_UnlockMutex(get_mutexes()->intersect);
	return (tmp_ray);
}
