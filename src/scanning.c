/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scanning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <fcecilie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 19:41:43 by fcecilie          #+#    #+#             */
/*   Updated: 2018/01/23 22:32:15 by shiro            ###   ########.fr       */
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
int	bidon(){printf("TEST2\n");return (0);}

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
	(void)q;
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
	//int			x;
	//int			y;
	t_ray		ray;

	t_thread_data thread_debut;
	t_thread_data thread_milieu_haut;
	t_thread_data thread_milieu_bas;
	t_thread_data thread_fin;

	SDL_Thread	*rendering;

	int ret;

	ray.equ.vc = *(t_vector*)&scn->cam->origin;
	ray.actual_refractive_i = 1;
	ray.tree = add_new_leaf(NULL, NULL, NULL, 0);

	//y = -1;

	ray.limit = 1;
	thread_debut = thread_data(-1, WIN_HEIGHT/4, scn, ray);
	ray.limit = 2;
	thread_milieu_haut = thread_data(WIN_HEIGHT / 4 - 1, 2 * WIN_HEIGHT / 4, scn, ray);
	ray.limit = 3;
	thread_milieu_bas = thread_data(2 * WIN_HEIGHT / 4 - 1, 3 * WIN_HEIGHT / 4, scn, ray);
	ray.limit = 4;
	thread_fin = thread_data(3 * WIN_HEIGHT / 4 - 1, WIN_HEIGHT, scn, ray);

	t_pxl_queue	**tmp;
	int i;

	tmp = get_pxl_queue(1);
	if (!((*tmp) = malloc(((thread_debut.y_end - thread_debut.y_begin - 1) * WIN_WIDTH + 1) * sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	i = -1;
	while (++i < (thread_debut.y_end - thread_debut.y_begin - 1) * WIN_WIDTH)
		(*tmp)[i].rendered = -2;
	(*tmp)[i].rendered = -1;

	tmp = get_pxl_queue(2);
	if (!((*tmp) = malloc(((thread_milieu_haut.y_end - thread_milieu_haut.y_begin - 1) * WIN_WIDTH + 1) * sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	i = -1;
	while (++i < (thread_milieu_haut.y_end - thread_milieu_haut.y_begin - 1) * WIN_WIDTH)
		(*tmp)[i].rendered = -2;
	(*tmp)[i].rendered = -1;

	tmp = get_pxl_queue(3);
	if (!((*tmp) = malloc(((thread_milieu_bas.y_end - thread_milieu_bas.y_begin - 1) * WIN_WIDTH + 1) * sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	i = -1;
	while (++i < (thread_milieu_bas.y_end - thread_milieu_bas.y_begin - 1) * WIN_WIDTH)
		(*tmp)[i].rendered = -2;
	(*tmp)[i].rendered = -1;

	tmp = get_pxl_queue(4);
	if (!((*tmp) = malloc(((thread_fin.y_end - thread_fin.y_begin - 1) * WIN_WIDTH + 1) * sizeof(t_pxl_queue))))
		exit_error("rt", "malloc");
	i = -1;
	while (++i < (thread_fin.y_end - thread_fin.y_begin - 1) * WIN_WIDTH)
		(*tmp)[i].rendered = -2;
	(*tmp)[i].rendered = -1;

	clock_t debut = clock();

	thread_debut.thread = SDL_CreateThread(scanning_multi, "thread 1", (void *)&thread_debut);
	thread_milieu_haut.thread = SDL_CreateThread(scanning_multi, "thread 2", (void *)&thread_milieu_haut);
	thread_milieu_bas.thread = SDL_CreateThread(scanning_multi, "thread 3", (void *)&thread_milieu_bas);
	thread_fin.thread = SDL_CreateThread(scanning_multi, "thread 4", (void *)&thread_fin);

	rendering = SDL_CreateThread(rendering_thread, "", NULL);

	SDL_WaitThread(thread_debut.thread, &ret);
	//printf("1 - done\n");
	SDL_WaitThread(thread_milieu_haut.thread, &ret);
	//printf("2 - done\n");
	SDL_WaitThread(thread_milieu_bas.thread, &ret);
	//printf("3 - done\n");
	SDL_WaitThread(thread_fin.thread, &ret);
	//printf("4 - done\n");
	SDL_WaitThread(rendering, NULL);
	//printf("rendering - done\n");

	/*thread_debut = thread_data(-1, WIN_HEIGHT, scn, ray);
	thread_debut.thread = SDL_CreateThread(scanning_multi, "thread 1", (void *)&thread_debut);
	SDL_WaitThread(thread_debut.thread, &ret);*/

	clock_t fin = clock();
	printf("%f\n", (double)(fin - debut)/CLOCKS_PER_SEC);


//	remove_leaf(ray.tree);
}
