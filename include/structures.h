/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:19:46 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/08 04:57:19 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define WIN_WIDTH 	1200
# define WIN_HEIGHT 650
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include "SDL2/SDL.h"
# endif

/*
	Structures pour gestion des threads avec la SDL, pê pas nécessaires
typedef enum		e_thread_state
{
	RUN,
	PAUSE,
	STOP
}					t_thread_state;
typedef struct		s_thread
{
	SDL_Thread		*ptr;
	SDL_mutex		*mutex;
	t_thread_state	state;
}					t_thread;
*/

typedef struct				s_sdl_core
{
	SDL_Window				*window;
	SDL_Renderer			*renderer;
	int						width;
	int						height;
	int						fullscreen;
}							t_sdl_core;

typedef struct				s_event
{
	SDL_EventType			type;
	void					*data;
	int						(*fct)();
	struct s_event			*next;
}							t_event;

typedef struct				s_evt_data
{
}							t_evt_data;

/*	Mes propre matrices, à changer si besoin est*/
typedef struct				s_matrix
{
	double					**mat;
	int						r;
	int						c;
}							t_matrix;

/*	Vecteur représentés sous la forme de vecteurs colonnes,
	si plus pratique utiliser 2 points*/
typedef struct				s_vector
{
	double					x;
	double					y;
	double					z;
}							t_vector;


/*	Oui c'est la même chose que le vecteur, on peut du coup soit ignorer le
	vecteur complètement et utiliser que des points, soit utiliser les points
	et les vecteurs pour plus de clareté, soit changer la forme des
	vecteurs*/
typedef struct				s_dot
{
	double					x;
	double					y;
	double					z;
}							t_dot;

typedef struct				s_trans_data
{
	t_dot						trans;
	t_dot						rot;
	t_dot						scale;
}							t_trans_data;

typedef struct				s_parequation
{
	t_vector				vc;
	t_vector				vd;
}							t_parequation;

typedef struct		s_ray
{
	t_parequation			equ;
	t_dot					inter;
	t_vector				normal;
	SDL_Color				color;
	struct s_object			*obj;
	struct s_light			*light;
	struct s_objs_tree		*tree;
	double					actual_refractive_i;
	double					percuted_refractive_i;
	double					limit;
	int						nb_intersect;
}					t_ray;

typedef enum				e_type
{
//	BOX, pour plus tard
	CONE,
	CYLINDER,
	PLANE,
	SPHERE
}							t_type;

typedef struct				s_obj_phys
{
	double					reflection_amount;
	double					refraction_amount;
	double					refractive_index;
	double					shininess;
}							t_obj_phys;

typedef struct				s_object
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	const t_vector			*(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_vector				normal;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						status;
}							t_object;

typedef struct				s_objs_comp
{
	t_dot					orig;
	SDL_Color				col;
	double					reflection_amount;
	double					refraction_amount;
	double					refractive_index;
	double					shininess;
}							t_objs_comp;

typedef struct				s_sphere
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	const t_vector			*(*get_normal)(t_dot *inter, t_object *obj);
	t_dot					origin;
	t_vector				normal;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						status;
	double					radius;
	double					r2;
}							t_sphere;

typedef struct				s_cylinder
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	const t_vector			*(*get_normal)(t_dot *inter, t_object *obj);
	t_dot					origin;
	t_vector				normal;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						status;
	double					radius;
	double					r2;
}							t_cylinder;

typedef struct				s_cone
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	const t_vector			*(*get_normal)(t_dot *inter, t_object *obj);
	t_dot					origin;
	t_vector				normal;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						status;
	double					angle;
	double					tanalpha2;
}							t_cone;

typedef struct				s_plane
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	const t_vector			*(*get_normal)(t_dot *inter, t_object *obj);
	t_dot					origin;
	t_vector				normal;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						status;
	
	double					a;
	double					b;
	double					c;
	double					d;
	double					z;
}							t_plane;

/* La box (le pavé quoi) pour plus tard
typedef struct		s_box
{
	const t_type	obj_type;
	double			(*intersect)();
	const t_vector	*(*get_normal)();
	t_dot			origin;
	t_vector		normal;
	SDL_Color		color;
	t_dot			fbl_corner;
	t_dot			btr_corner;
	t_plane			*front;
	t_plane			*back;
	t_plane			*top;
	t_plane			*bottom;
	t_plane			*left;
	t_plane			*right;
}					t_box;
*/

typedef enum				e_light_type
{
	ORB,
	PARALLEL,
	SPOT
}							t_light_type;

typedef struct	s_light_crd
{
	t_dot		orig;
	t_vector	direction;
}				t_light_crd;

typedef struct				s_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot *pos, struct s_light *light);
	int						(*is_in_light)(struct s_light *light, t_ray *light_ray);
	double					power;
}							t_light;

/*
** parallel_light hérite de light
*/
typedef struct				s_parallel_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot *pos, t_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;
}							t_parallel_light;

/*
** spotlight hérite de light
*/
typedef struct				s_spotlight
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot *pos, t_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;
	t_dot					orig;
	double					aperture;
}							t_spotlight;

/*
** orb_light hérite de spotlight
*/
typedef struct				s_orb_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot *pos, t_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;
	t_dot					orig;
	double					aperture;
}							t_orb_light;

//	ecran imaginaire qui permet de definir le vecteur camera -> pixel;
typedef struct				s_view_plane
{
	t_dot					up_left;
	t_vector				front;
	t_vector				up;
	t_vector				right;
	t_vector				size;
	double					fov;
}							t_view_plane;

typedef struct				s_camera
{
	t_dot					origin;
	double					focal;
	t_vector				angle;
	double					angle_x;
	double					angle_y;
	double					angle_z;
	t_view_plane			*vp;
}							t_camera;

typedef struct				s_list_objs
{
	t_object				*obj;
	struct s_list_objs		*next;
}							t_list_objs;

typedef struct				s_objs_tree
{
	t_object				*obj;
	int						lvl;
	struct s_objs_tree		*root;
	struct s_objs_tree		*reflected;
	struct s_objs_tree		*refracted;
}							t_objs_tree;

typedef struct				s_list_lights
{
	t_light					*light;
	struct s_list_lights	*next;
}							t_list_lights;

typedef struct				s_scene
{
	double					brightness;
	t_camera				*cam;
	t_list_lights			*lights;
	t_list_objs				*objects;
}							t_scene;

#endif
