/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/24 12:49:00 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

t_parequation	transform_equ(t_ray *ray, t_object *obj)
{
	t_parequation	trs;

	trs.vc = (t_vector){ray->equ.vc.x - obj->origin.x,
		ray->equ.vc.y - obj->origin.y, ray->equ.vc.z - obj->origin.z};
	mult_vect(&trs.vc, obj->trans_iconst, &trs.vc);
	mult_vect(&trs.vd, obj->trans_idir, &ray->equ.vd);
	return (trs);
}

void			transform_inter(t_ray *ray, t_object *obj)
{
	mult_vect(&ray->normal, obj->trans_norm, &ray->normal);
	mult_vect((t_vector*)&ray->inter, obj->trans_const, (t_vector*)&ray->inter);
	ray->inter = (t_dot){ray->inter.x + obj->origin.x,
		ray->inter.y + obj->origin.y, ray->inter.z + obj->origin.z};
}

SDL_Color		effects(t_ray *ray, t_scene *scn, SDL_mutex *mutex_leaf)
{
	SDL_Color	reflect_ray;
	SDL_Color	refract_ray;

	if (check_intersect(ray, scn->objects) > 0)
	{
		ray->color = shadows(ray, scn);
		reflect_ray = reflect(ray, scn, mutex_leaf);
		refract_ray = refract(ray, scn, mutex_leaf);
		get_reflected_col(ray, ray->obj, reflect_ray);
		get_refracted_col(ray, ray->obj, refract_ray);
		return (ray->color);
	}
	return (ray->color = (SDL_Color){0, 0, 0, 255});
}

int				scanning_multi(void *data_void)
{
	t_thread_data	*data;
	int				y;
	int				x;
	int				q;
	t_ray		ray;

	data = (t_thread_data *)data_void;
	ray.equ.vc = *(t_vector*)&data->scn->cam->origin;
	ray.actual_refractive_i = 1;
	ray.limit = 1;
	ray.tree = add_new_leaf(NULL, NULL, NULL, 0);
	q = -1;
	y = data->y_begin;
	while (++y < data->y_end)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			view_plane_vector(x, y, data->scn->cam, &ray.equ.vd);
			effects(&ray, data->scn, data->mutex_leaf);
			(*get_pxl_queue((int)data->ray.limit))[++q] = (t_pxl_queue){0, x, y, ray.color};
		}
	}
	remove_leaf(ray.tree);
	return (0);
}

void			scanning(t_scene *scn)
{
	t_thread_data	*threads;
	SDL_Thread		*rendering;
	int	i;


	threads = init_thread_array(scn, get_sdl_core()->nb_threads);
	(void)threads;
	i = 0;
	clock_t debut = clock();
	while (i < get_sdl_core()->nb_threads)
	{
		threads[i].thread = SDL_CreateThread(scanning_multi, "thread", (void *)&threads[i]);
		i++;
	}
	if (!(rendering = SDL_CreateThread(rendering_thread, "", NULL)))
		exit_custom_error("rt: SDL2: SDL_CreateThread: ", (char*)SDL_GetError());
	i = 0;
	while (i < get_sdl_core()->nb_threads)
	{
		SDL_WaitThread(threads[i].thread, NULL);
		printf("%d - done\n", i + 1);
		i++;
	}
	SDL_WaitThread(rendering, NULL);
	clock_t fin = clock();
	printf("%f\n", (double)(fin - debut)/CLOCKS_PER_SEC);
}
