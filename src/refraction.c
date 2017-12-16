/*============================================================================*/
/*                                                                            */
/*        fichier :   refraction.c                                            */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

int		get_refracted_vect(t_vector *dir, const t_vector *norm,
			double n1, double n2)
{
	double		cos_t1;
	double		cos_t2;
	double		n1_n2;
	t_vector	u_dir;
	t_vector	u_norm;

	cos_t1 = get_vect_lenght(dir);
	cos_t2 = get_vect_lenght(norm);
	u_dir = vector(dir->x / cos_t1, dir->y / cos_t1, dir->z / cos_t1);
	u_norm = vector(norm->x / cos_t2, norm->y / cos_t2, norm->z / cos_t2);
	cos_t1 = vect_dot_product(&u_norm,
							&(t_vector){-u_dir.x, -u_dir.y, -u_dir.z});
	n1_n2 = n1 / n2;
	if ((cos_t2 = (1 - pow(n1_n2, 2) * (1 - pow(cos_t1, 2)))) < 0)
	{
		*dir = get_reflected_vect(dir, norm);
		return (1);
	}
	else
		cos_t2 = sqrt(cos_t2);
	if (cos_t1 > 0)
		cos_t2 = -cos_t2;
	*dir = (t_vector){n1_n2 * u_dir.x + (n1_n2 * cos_t1 + cos_t2) * u_norm.x,
					n1_n2 * u_dir.y + (n1_n2 * cos_t1 + cos_t2) * u_norm.y,
					n1_n2 * u_dir.z + (n1_n2 * cos_t1 + cos_t2) * u_norm.z};
	return (0);
}

void	get_refracted_col(t_ray *ray, t_object *src,
			SDL_Color refracted_obj_col)
{
	ray->color.r = (ray->color.r * (1 - src->obj_light.refraction_amount)) +
			(refracted_obj_col.r * src->obj_light.refraction_amount);
	ray->color.g = (ray->color.g * (1 - src->obj_light.refraction_amount)) +
			(refracted_obj_col.g * src->obj_light.refraction_amount);
	ray->color.b = (ray->color.b * (1 - src->obj_light.refraction_amount)) +
			(refracted_obj_col.b * src->obj_light.refraction_amount);
}

SDL_Color	refract(t_ray *ray, t_scene *scn)
{
	t_ray			ref_ray;
	t_objs_tree		*first;
	SDL_Color		ret;
	int				total_ref;

	ref_ray = *ray;
	if (ray->obj->obj_light.refraction_amount == 0)
		return (ref_ray.color);
	if (ray->limit < 0.1)
		return ((SDL_Color){0, 0, 0, 255});
	ref_ray.limit -= (1 - ray->obj->obj_light.refraction_amount) / 100;
	if (ray->nb_intersect == 2)
	{
		if (!(total_ref = get_refracted_vect(&ref_ray.equ.vd, &ray->normal, ray->tree->obj ?  ray->tree->obj->obj_light.refractive_index : 1, ray->obj ? ray->obj->obj_light.refractive_index : 1)))
			ref_ray.tree = add_new_leaf(ray->tree, &ray->tree->refracted, ray->obj, ray->tree->lvl + 1);
		else
			ref_ray.tree = add_new_leaf(ray->tree, &ray->tree->refracted, ray->tree->obj, ray->tree->lvl);
	}
	else
	{
		if (!(first = goto_root_obj(ray->tree, ray->obj)))
			first = goto_root_obj(ray->tree, ray->tree->obj);
		if (!first->root)
			return ((SDL_Color){0, 0, 0, 255});
		if (first->lvl < ray->tree->lvl)
			total_ref = get_refracted_vect(&ref_ray.equ.vd, &ray->normal, ray->tree->obj ?  ray->tree->obj->obj_light.refractive_index : 1, ray->obj ? ray->obj->obj_light.refractive_index : 1);
		else
			total_ref = get_refracted_vect(&ref_ray.equ.vd, &ray->normal, ray->tree->obj ? ray->tree->obj->obj_light.refractive_index : 1, (first->root && first->root->obj) ? first->root->obj->obj_light.refractive_index : 1);

		if (!total_ref)
			ref_ray.tree = add_new_leaf(first->root ? first->root : first, NULL, first->lvl < ray->tree->lvl ? ray->tree->obj : first->root->obj, first->lvl < ray->tree->lvl ? ray->tree->lvl : first->root->lvl);
		else
			ref_ray.tree = add_new_leaf(ray->tree, &ray->tree->refracted, ray->obj, ray->tree->lvl);
	}
	ref_ray.equ.vc = vector(ray->inter.x + (1 / POW) * ray->equ.vd.x,
			ray->inter.y + (1 / POW) * ray->equ.vd.y,
			ray->inter.z + (1 / POW) * ray->equ.vd.z);
	ret = effects(&ref_ray, scn);
	remove_leaf(ref_ray.tree);
	return (ret);
}
