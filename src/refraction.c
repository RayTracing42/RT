/*============================================================================*/
/*                                                                            */
/*        fichier :   refraction.c                                            */
/*                                                                            */
/*        auteur  :   fcecilie                                                */
/*        adresse :   fcecilie@student.42.fr                                  */
/*                                                                            */
/*============================================================================*/

#include "rt.h"

void	get_refracted_vect(t_vector *dir, const t_vector *norm,
			double actual_refractive_index, double percuted_refractive_index)
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
	n1_n2 = actual_refractive_index / percuted_refractive_index;
	cos_t2 = sqrt(1 - pow(n1_n2, 2) * (1 - pow(cos_t1, 2)));
	if (cos_t1 > 0)
		cos_t2 = -cos_t2;
	*dir = (t_vector){n1_n2 * u_dir.x + (n1_n2 * cos_t1 + cos_t2) * u_norm.x,
					n1_n2 * u_dir.y + (n1_n2 * cos_t1 + cos_t2) * u_norm.y,
					n1_n2 * u_dir.z + (n1_n2 * cos_t1 + cos_t2) * u_norm.z};
	if ((1 - pow(n1_n2, 2) * (1 - pow(cos_t1, 2))) < 0)
		printf("%f\n", dir->x);
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
/*
static void	set_nodes(t_ray *ray, t_ray *ref_ray)
{
	if (ray->nb_intersect == 2)
	{
		if (!if_node_exist(ref_ray->l_objs, ray->obj))
		{
			add_node(&ref_ray->l_objs, ray->obj);
			ref_ray->percuted_refractive_i =
				ray->obj->obj_light.refractive_index;
		}
		else
		{
			remove_node(&ref_ray->l_objs, ray->obj);
			ref_ray->actual_refractive_i =
				ray->obj->obj_light.refractive_index;
			if (ref_ray->l_objs)
				ref_ray->percuted_refractive_i =
					ref_ray->l_objs->obj->obj_light.refractive_index;
			else
				ref_ray->percuted_refractive_i = 1;
		}
	}
}
*/
SDL_Color	refract(t_ray *ray, t_scene *scn)
{
	t_ray			ref_ray;
	t_objs_tree		*first;
	SDL_Color		ret;
	ref_ray = *ray;
	if (ray->obj->obj_light.refraction_amount == 0)
		return (ref_ray.color);
	if (ray->limit < 0.1)
		return ((SDL_Color){0, 0, 0, 255});
	ref_ray.limit -= (1 - ray->obj->obj_light.refraction_amount) / 100;
	if (ray->nb_intersect == 2)
	{
		ref_ray.tree = add_new_leaf(ray->tree, &ray->tree->refracted, ray->obj, ray->tree->lvl + 1);
		printf("R : %p (%p)\n", ref_ray.tree, ray->tree);
	}
	else
	{
		first = goto_root_obj(ray->tree, ray->obj);
		if (!first)
			printf("R : (%p)\n", ray->tree);
		ref_ray.tree = add_new_leaf(first->root, NULL, first->lvl < ray->tree->lvl ? ray->obj : first->root->obj, first->lvl < ray->tree->lvl ? ray->tree->lvl : first->root->lvl);
		printf("R : %p (%p | New : %p)\n", ref_ray.tree, ray->tree, first ? first->root : first);
	}
	get_refracted_vect(&ref_ray.equ.vd, &ray->normal, ray->tree->obj ?  ray->tree->obj->obj_light.refractive_index : 1, ref_ray.tree->obj ? ref_ray.tree->obj->obj_light.refractive_index : 1);
	ref_ray.equ.vc = vector(ray->inter.x + 0.00001 * ray->equ.vd.x,
			ray->inter.y + 0.00001 * ray->equ.vd.y,
			ray->inter.z + 0.00001 * ray->equ.vd.z);
	ret = effects(&ref_ray, scn);
	//remove_leaf(ref_ray.tree);
	return (ret);
}
