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
		refracted_ray.equ.vc = vector(ray->inter.x, ray->inter.y, ray->inter.z);
		get_refracted_vect(&refracted_ray.equ.vd, &ray->normal, ray->refractive_index, ray->obj->obj_light.refractive_index);
		if (ray->obj->intersect(&refracted_ray, &ray->obj, 2) > 0 && ray->obj->obj_type != PLANE)
		{
			refracted_ray.normal = *ray->obj->get_normal(&refracted_ray.inter, ray->obj);
//			refracted_ray.normal = vector_opposite(refracted_ray.normal.x, refracted_ray.normal.y, refracted_ray.normal.z);
			
			refracted_ray.equ.vc = vector(refracted_ray.inter.x, refracted_ray.inter.y, refracted_ray.inter.z);
			get_refracted_vect(&refracted_ray.equ.vd, &refracted_ray.normal, ray->obj->obj_light.refractive_index, ray->refractive_index);
			return (effects(&refracted_ray, scn));
		}
		else
			return (effects(&refracted_ray, scn));
	}
	return (refracted_ray.color);
}
