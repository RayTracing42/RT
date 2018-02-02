/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/30 01:23:20 by fcecilie         ###   ########.fr       */
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
	mult_vect(&ray->normal, ray->obj->trans_norm, &ray->normal);
	mult_vect((t_vector*)&ray->inter, ray->obj->trans_const, (t_vector*)&ray->inter);
	ray->inter = (t_dot){ray->inter.x + ray->obj->origin.x,
		ray->inter.y + ray->obj->origin.y, ray->inter.z + ray->obj->origin.z};
	ray->obj = obj;
}

void			valid_ray(t_ray *r1, double *t_r1, t_ray *r2, double *t_r2)
{
	*r1 = *r2;
	*t_r1 = *t_r2;
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

static int		scanning_multi(void *data_void)
{
	t_thread_data		*data;
	t_scanning_index	i;
	t_ray				ray;

	data = (t_thread_data *)data_void;
	ray.equ.vc = *(t_vector*)&data->scn->cam->origin;
	ray.actual_refractive_i = 1;
	ray.limit = 1;
	ray.tree = add_new_leaf(NULL, NULL, NULL, 0);
	i.q = -1;
	i.y = data->y_begin;
	while (++i.y < data->y_end)
	{
		i.x = -1;
		while (++i.x < WIN_WIDTH)
		{
			view_plane_vector(i.x, i.y, data->scn->cam, &ray.equ.vd);
			effects(&ray, data->scn);
			(*get_pxl_queue(data->n_thread))[++i.q] = (t_pxl_queue){0, i.x, i.y, ray.color};
		}
	}
	remove_leaf(ray.tree);
	return (0);
}

void			scanning(t_scene *scn)
{
	t_thread_data	*threads;
	SDL_Thread		*rendering;
	int				i;
	struct timeb	debut;
	struct timeb	fin;

	threads = init_thread_array(scn, get_sdl_core()->nb_threads);
	i = -1;
	ftime(&debut);
	while (++i < get_sdl_core()->nb_threads)
	{
		if (!(threads[i].thread = SDL_CreateThread(scanning_multi, "thread", (void*)&threads[i])))
			exit_custom_error("rt: SDL2: SDL_CreateThread: ", (char*)SDL_GetError());;
	}
	if (!(rendering = SDL_CreateThread(rendering_thread, "", NULL)))
		exit_custom_error("rt: SDL2: SDL_CreateThread: ", (char*)SDL_GetError());
	i = -1;
	while (++i < get_sdl_core()->nb_threads)
		SDL_WaitThread(threads[i].thread, NULL);
	SDL_WaitThread(rendering, NULL);
	free(threads);
	ftime(&fin);

	printf("total time: %fs\n", (fin.time + (fin.millitm)/1000.0 - debut.time - debut.millitm/1000.0));
}
