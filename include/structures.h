/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:19:46 by edescoin          #+#    #+#             */
/*   Updated: 2018/02/03 16:09:05 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define WIN_WIDTH	1200
# define WIN_HEIGHT	650
# define _A			0
# define _B			1
# define _C			2
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include "SDL2/SDL.h"
# endif

typedef struct	s_mutexes
{
	SDL_mutex	*intersect;
}				t_mutexes;

typedef struct	s_pxl_queue
{
	int	rendered;
	int	x;
	int	y;
	SDL_Color	col;
}				t_pxl_queue;

typedef struct	s_scanning_index
{
	int	x;
	int	y;
	int	q;
}				t_scanning_index;

typedef struct				s_sdl_core
{
	SDL_Window				*window;
	SDL_Renderer			*renderer;
	SDL_Texture				*target;
	int						width;
	int						height;
	int						nb_threads;
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
	double					shad_opacity;
	double					actual_refractive_i;
	double					percuted_refractive_i;
	double					limit;
	int						nb_intersect;

	int						debug;
}					t_ray;

typedef struct		s_couple_ray
{
	t_ray					a;
	t_ray					b;
	double					ta;
	double					tb;
}					t_couple_ray;

typedef struct		s_list_ray
{
	t_ray					r;
	double					t;
	struct s_list_ray		*next;
}					t_list_ray;

typedef enum				e_type
{
	BOX,
	CONE,
	CYLINDER,
	HYPERBOLOID,
	PLANE,
	SPHERE,
	TRIANGLE
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
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
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
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	double					radius;
	double					r2;
}							t_sphere;

typedef struct				s_cylinder
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	double					radius;
	double					r2;
}							t_cylinder;

typedef struct				s_cone
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	int						upper;
	double					angle;
	double					tanalpha2;
}							t_cone;

typedef struct				s_plane
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_vector				normal;
	double					a;
	double					b;
	double					c;
	double					d;
	double					z;
}							t_plane;

/*
** t_triangle hérite de plane puisque les calculs se ressemblent bcp
*/
typedef struct				s_triangle
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_vector				normal;
	double					a;
	double					b;
	double					c;
	double					d;
	double					z;
	double					aA;
	double					aB;
	t_dot					dA;
	t_dot					dB;
	t_dot					dC;
	t_vector				vAB;
	t_vector				vBA;
	t_vector				vBC;
}							t_triangle;

typedef struct		s_box
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_dot					size;
	t_dot					fbl_corner;
	t_dot					btr_corner;
	t_plane					*front;
	t_plane					*back;
	t_plane					*top;
	t_plane					*bottom;
	t_plane					*left;
	t_plane					*right;
}					t_box;

typedef struct		s_box_intersect
{
	t_box			*box;
	t_dot			inter;
	int				i;
	double			t;
	t_plane			*p;
}					t_box_intersect;

typedef struct	s_hyperboloid
{
	const t_type			obj_type;
	int						(*is_in_obj)(t_dot *i, struct s_object *obj);
	double					(*intersect)(t_ray *ray, t_parequation e, struct s_object *obj, int i);
	t_vector				(*get_normal)(t_dot *inter, struct s_object *obj);
	t_dot					origin;
	t_matrix				*trans_const;
	t_matrix				*trans_iconst;
	t_matrix				*trans_idir;
	t_matrix				*trans_norm;
	SDL_Color				color;
	t_obj_phys				obj_light;
	struct s_list_objs		*limit;
	struct s_list_objs		*negative_obj;
	int						is_light;
	int						status;

	t_vector				normal;
	double					a2;
	double					b2;
	double					c2;
	double					d;
}				t_hyperboloid;

typedef enum				e_light_type
{
	OBJECT,
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
	t_vector				(*get_ray_vect)(t_dot pos, struct s_light *light);
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
	t_vector				(*get_ray_vect)(t_dot pos, t_light *light);
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
	t_vector				(*get_ray_vect)(t_dot pos, t_light *light);
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
	t_vector				(*get_ray_vect)(t_dot pos, t_light *light);
	int						(*is_in_light)(t_light *light, t_ray *light_ray);
	double					power;
	t_dot					orig;
	double					aperture;
}							t_orb_light;

typedef struct	s_obj_light
{
	const t_light_type		type;
	SDL_Color				color;
	t_vector				direction;
	t_vector				(*get_ray_vect)(t_dot pos, struct s_light *light);
	int						(*is_in_light)(struct s_light *light, t_ray *light_ray);
	double					power;

	t_object				*shape;
}				t_obj_light;

//	ecran imaginaire qui permet de definir le vecteur camera -> pixel;
typedef struct				s_view_plane
{
	t_dot					up_left;
	t_vector				front;
	t_vector				up;
	t_vector				right;
	t_vector				size;
}							t_view_plane;

typedef struct				s_camera
{
	t_dot					origin;
	t_dot					angle;
	double					depth;
	double					focal;
	t_view_plane			vp;
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
	t_camera				cam;
	t_list_lights			*lights;
	t_list_objs				*objects;
}							t_scene;

typedef struct				s_thread_data
{
	SDL_Thread	*thread;
	t_scene		scn;
	int			n_thread;
	int			y_begin;
	int			y_end;
}							t_thread_data;

#endif
