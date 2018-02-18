/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/02/18 19:04:10 by edescoin         ###   ########.fr       */
=======
/*   Updated: 2018/02/18 18:35:29 by edescoin         ###   ########.fr       */
>>>>>>> AAliasing
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			valid_ray(t_ray *r1, double *t_r1, t_ray *r2, double *t_r2)
{
	*r1 = *r2;
	*t_r1 = *t_r2;
}

SDL_Color		effects(t_ray *ray, t_scene *scn)
{
	SDL_Color	reflect_ray;
	SDL_Color	refract_ray;

	if (check_intersect(ray, scn->objects, 1, NULL) > 0)
	{
		if (ray->obj->is_light)
			return (ray->color);
		ray->color = shadows(ray, scn);
		reflect_ray = reflect(ray, scn);
		refract_ray = refract(ray, scn);
		get_reflected_col(ray, ray->obj, reflect_ray);
		get_refracted_col(ray, ray->obj, refract_ray);
		return (ray->color);
	}
	return (ray->color = (SDL_Color){0, 0, 0, 0});
}
<<<<<<< HEAD
/*
static void		randomize_cam_orig(t_camera *cam, struct drand48_data *buff)
=======

static void		randomize_cam_orig(t_camera *cam)
>>>>>>> AAliasing
{
	double	r;
	int		s;

	r = drand48();
	s = (int)(r * 10) % 2 ? -1 : 1;
	r = drand48();
	cam->origin.x += s * r * cam->depth;
	r = drand48();
	s = (int)(r * 10) % 2 ? -1 : 1;
	r = drand48();
	cam->origin.y += s * r * cam->depth;
	r = drand48();
	s = (int)(r * 10) % 2 ? -1 : 1;
	r = drand48();
	cam->origin.z += s * r * cam->depth;
}
*/
static void		scan_pixel(t_ray *ray, t_thread_data *data, t_scanning_index *i)
{
	ray->equ.vc = *(t_vector*)&data->scn.cam.origin;
	view_plane_vector(i->x, i->y, &data->scn.cam, &ray->equ.vd);
	effects(ray, &data->scn);
	(*get_pxl_queue(data->n_thread))[++i->q] = (t_pxl_queue){-2, i->x, i->y,
															ray->color};
	(*get_pxl_queue(data->n_thread))[i->q].rendered = 0;
}

static int		scanning_multi(void *data_void)
{
	t_thread_data		*data;
	t_scanning_index	i;
	t_ray				ray;
	t_dot				cam_orig;
<<<<<<< HEAD
	//struct drand48_data	buff;

	data = (t_thread_data *)data_void;
	//srand48_r(time(NULL) * data->n_thread, &buff);
=======

	data = (t_thread_data *)data_void;
>>>>>>> AAliasing
	cam_orig = data->scn.cam.origin;
	ray.actual_refractive_i = 1;
	ray.limit = 1;
	ray.tree = add_new_leaf(NULL, NULL, NULL, 0);
	i.q = -1;
	i.y = data->y_begin;
	while (++i.y < data->y_end)
	{
		i.x = -1;
		while (++i.x < get_sdl_core()->width)
		{
			data->scn.cam.origin = cam_orig;
<<<<<<< HEAD
			//randomize_cam_orig(&data->scn.cam, &buff);
			scan_pixel(&ray, data, &i);
=======
			randomize_cam_orig(&data->scn.cam);
			ray.equ.vc = *(t_vector*)&data->scn.cam.origin;
			view_plane_vector(i.x, i.y, &data->scn.cam, &ray.equ.vd);
			effects(&ray, &data->scn);
			(*get_pxl_queue(data->n_thread))[++i.q] = (t_pxl_queue){-2, i.x, i.y, ray.color};
			(*get_pxl_queue(data->n_thread))[i.q].rendered = 0;
>>>>>>> AAliasing
		}
	}
	remove_leaf(ray.tree);
	return (0);
}

static void		print_time(t_time t)
{
	ft_putstr("total time: ");
	ft_putnbr(t.fin.time + (t.fin.millitm) / 1000.0 -
			t.debut.time - t.debut.millitm / 1000.0);
	ft_putstr("s\n");
}

void			scanning(t_scene *scn)
{
	t_thread_data	*threads;
	SDL_Thread		*rendering;
	int				i;
	t_time			t;

	threads = init_thread_array(scn, get_sdl_core()->nb_threads);
	i = -1;
	ftime(&t.debut);
	while (++i < get_sdl_core()->nb_threads)
		if (!(threads[i].thread = SDL_CreateThread(scanning_multi, "thread",
													(void*)&threads[i])))
			exit_custom_error("rt: SDL2: SDL_CreateThread: ",
							(char*)SDL_GetError());
	if (!(rendering = SDL_CreateThread(rendering_thread, "", NULL)))
		exit_custom_error("rt: SDL2: SDL_CreateThread: ",
						(char*)SDL_GetError());
	i = -1;
	while (++i < get_sdl_core()->nb_threads)
		SDL_WaitThread(threads[i].thread, NULL);
	SDL_WaitThread(rendering, NULL);
	free(threads);
	ftime(&t.fin);
	print_time(t);
}
