
#include "rt.h"

int		limit_loop(t_ray *tmp_ray, t_object *father)
{
	t_list_objs	*l;
	t_plane		*p;
	t_ray		trans_ray;

	l = father->limit;
	while (l)
	{
		p = (t_plane *)l->obj;
		if (l->obj != tmp_ray->obj)
		{
			if (p->lim_type == LOCAL)
				if (!(is_in_local_limit(&tmp_ray->inter, p)))
					return (0);
			if (p->lim_type == GLOBAL)
			{
				trans_ray = *tmp_ray;
				transform_inter(&trans_ray, trans_ray.obj);
				if (!(is_in_global_limit(&trans_ray.inter, p)))
					return (0);
			}
		}
		l = l->next;
	}
	return (1);
}

void	normalized_diff(t_plane *p, t_dot *trans)
{
	double		dist;
	double		angle;
	t_vector	n;
	t_vector	o;

	o = (t_vector){p->orig_diff.x, p->orig_diff.y, p->orig_diff.z};
	if (!(o.x == 0 && o.y == 0 && o.z == 0))
	{
		n = p->normal;
		vect_normalize(&n);
		vect_normalize(&o);
		angle = angle_between_vectors(n, o);
		dist = get_vect_lenght(&p->orig_diff) * cos(angle * M_PI / 180);
		p->norm_diff = (t_vector){n.x * dist, n.y * dist, n.z * dist};
	}
	else
		p->norm_diff = (t_vector){0, 0, 0};
	trans->x += p->norm_diff.x;
	trans->y += p->norm_diff.y;
	trans->z += p->norm_diff.z;
}

int		empty_limit(t_ray *ray, t_ray *tmp_ray, t_object *father)
{
	t_plane *p;

	p = (t_plane *)tmp_ray->obj;
	if (limit_loop(tmp_ray, father))
	{
		transform_inter(tmp_ray, tmp_ray->obj);
		*ray = *tmp_ray;
		return (1);
	}
	return (0);
}

int		full_global_limit(t_ray *ray, t_ray *tmp_ray, t_object *father)
{
	t_plane *p;
	t_vector	center;

	ray = (t_ray *)ray;
	tmp_ray = (t_ray *)tmp_ray;
	father = (t_object *)father;

	p = (t_plane *)tmp_ray->obj;
		center = (t_vector){0, 0, 0};
		mult_vect(&center, father->trans_const, &center);
		center.x += father->origin.x;
		center.y += father->origin.y;
		center.z += father->origin.z;
//			printf("cent : (%.2f, %.2f, %.2f)\n", center.x, center.y, center.z);
	
			
//	printf("(%.2f, %.2f, %.2f)\n", tmp_ray->inter.x, tmp_ray->inter.y, tmp_ray->inter.z);
//		if (global_limit_loop(tmp_ray, father))
//		{
	if (transformed_local_limit_loop(tmp_ray, father))
	{
			transform_inter(tmp_ray, tmp_ray->obj);
			tmp_ray->inter.x -= center.x;
			tmp_ray->inter.y -= center.y;
			tmp_ray->inter.z -= center.z;
			if (father->is_in_obj(&tmp_ray->inter, father))
			{
			tmp_ray->inter.x += center.x;
			tmp_ray->inter.y += center.y;
			tmp_ray->inter.z += center.z;

				*ray = *tmp_ray;
				return (1);
			}
//		}
	}
	return (0);
}

int		full_limit(t_ray *ray, t_ray *tmp_ray, t_object *father)
{
	t_plane *p;

	p = (t_plane *)tmp_ray->obj;
	if (global_limit_loop(tmp_ray, father))
	{
		tmp_ray->inter.x += p->norm_diff.x;
		tmp_ray->inter.y += p->norm_diff.y;
		tmp_ray->inter.z += p->norm_diff.z;
		if (father->is_in_obj(&tmp_ray->inter, father))
		{
			if (local_limit_loop(tmp_ray, father))
			{
				transform_inter(tmp_ray, tmp_ray->obj);
				*ray = *tmp_ray;
				return (1);
			}
		}
	}
	return (0);
}
