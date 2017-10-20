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
	double		cos_theta1;
	double		cos_theta2;
	double		n1_by_n2;
	t_vector	u_dir;
	t_vector	u_norm;
	
	cos_theta1 = get_vect_lenght(dir);
	cos_theta2 = get_vect_lenght(norm);
	u_dir = vector(dir->x / cos_theta1, dir->y / cos_theta1, dir->z / cos_theta1);
	u_norm = vector(norm->x / cos_theta2, norm->y / cos_theta2, norm->z / cos_theta2);
	cos_theta1 = vect_dot_product(&u_norm, &(t_vector){-u_dir.x, -u_dir.y, -u_dir.z});
	n1_by_n2 = actual_refractive_index / percuted_refractive_index;
	cos_theta2 = sqrt(1 - pow(n1_by_n2, 2) * (1 - pow(cos_theta1, 2)));
	if (cos_theta1 > 0)
	{
		dir->x = n1_by_n2 * u_dir.x + (n1_by_n2 * cos_theta1 - cos_theta2) * u_norm.x;
		dir->y = n1_by_n2 * u_dir.y + (n1_by_n2 * cos_theta1 - cos_theta2) * u_norm.y;
		dir->z = n1_by_n2 * u_dir.z + (n1_by_n2 * cos_theta1 - cos_theta2) * u_norm.z;
	}
	else
	{
		dir->x = n1_by_n2 * u_dir.x + (n1_by_n2 * cos_theta1 + cos_theta2) * u_norm.x;
		dir->y = n1_by_n2 * u_dir.y + (n1_by_n2 * cos_theta1 + cos_theta2) * u_norm.y;
		dir->z = n1_by_n2 * u_dir.z + (n1_by_n2 * cos_theta1 + cos_theta2) * u_norm.z;
	}
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
	t_ray			refracted_ray;

	refracted_ray = *ray;
	if (ray->obj->obj_light.refraction_amount != 0)
	{
		if (ray->limit < 0.1)
			return ((SDL_Color){0, 0, 0, 255});
		refracted_ray.limit = refracted_ray.limit - (1 - ray->obj->obj_light.refraction_amount) / 100;
		if (ray->nb_intersect == 2)
		{
			if (!if_node_exist(refracted_ray.l_objs, ray->obj))
			{
				add_node(&refracted_ray.l_objs, ray->obj);
				refracted_ray.pri = ray->obj->obj_light.refractive_index;
			}
			else
			{
				remove_node(&refracted_ray.l_objs, ray->obj);
				refracted_ray.ari = ray->obj->obj_light.refractive_index;
				if (refracted_ray.l_objs)
					refracted_ray.pri = refracted_ray.l_objs->obj->obj_light.refractive_index;
				else
					refracted_ray.pri = 1;
			}
		}
		get_refracted_vect(&refracted_ray.equ.vd, &ray->normal, ray->ari, ray->pri);
		refracted_ray.equ.vc = vector(ray->inter.x + 0.00001 * ray->equ.vd.x,
				ray->inter.y + 0.00001 * ray->equ.vd.y,
				ray->inter.z + 0.00001 * ray->equ.vd.z);
		if (ray->nb_intersect == 2)
			refracted_ray.ari = refracted_ray.pri;
		return (effects(&refracted_ray, scn));
	}
	return (refracted_ray.color);
}
