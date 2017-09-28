/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:19:46 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/28 17:39:49 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Branch: scanning Find file Copy pathRT/includes/structures.h
4fa20db  2 hours ago
@fcecilie fcecilie Sauvegarde 28/09/2017
1 contributor
RawBlameHistory
316 lines (283 sloc)  6.43 KB
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 16:19:46 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/06 00:52:49 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H
# define WIN_WIDTH 	1200
# define WIN_HEIGHT 650
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include <SDL2/SDL.h>
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
}							t_obj_phys;

typedef struct				s_object
{
	const t_type			obj_type;
	double					(*intersect)();
	const t_vector			*(*get_normal)();
	t_dot					origin;
	t_vector				dir;
	t_vector				normal;
	SDL_Color				color;
	t_obj_phys				obj_light;
}							t_object;

typedef struct				s_objs_comp
{
	t_dot					origin;
	t_vector				dir;
	SDL_Color				color;
}							t_objs_comp;

typedef struct				s_sphere
{
	const t_type			obj_type;
	double					(*intersect)();
	const t_vector			*(*get_normal)();
	t_dot					origin;
	t_vector				dir;
	t_vector				normal;
	SDL_Color				color;
	t_obj_phys				obj_light;
	double					radius;
	double					r2;
}							t_sphere;

typedef struct				s_cylinder
{
	const t_type			obj_type;
	double					(*intersect)();
	const t_vector			*(*get_normal)();
	t_dot					origin;
	t_vector				dir;
	t_vector				normal;
	SDL_Color				color;
	t_obj_phys				obj_light;
	double					radius;
	double					r2;
	double					height_top;
	double					height_bottom;
}							t_cylinder;

typedef struct				s_cone
{
	const t_type			obj_type;
	double					(*intersect)();
	const t_vector			*(*get_normal)();
	t_dot					origin;
	t_vector				dir;
	t_vector				normal;
	SDL_Color				color;
	t_obj_phys				obj_light;
	double					angle;
	double					tanalpha2;
	double					height_top;
	double					height_bottom;
}							t_cone;

typedef struct				s_plane
{
	const t_type			obj_type;
	double					(*intersect)();
	const t_vector			*(*get_normal)();
	t_dot					origin;
	t_vector				dir;
	t_vector				normal;
	SDL_Color				color;
	t_obj_phys				obj_light;
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

typedef struct				s_light
{
	const t_light_type		type;
	t_vector				direction;
	SDL_Color				color;
	int						(*is_in_light)();
	void					(*get_ray_vect)();
}							t_light;

/*
** parallel_light hérite de light
*/
typedef struct				s_parallel_light
{
	const t_light_type		type;
	t_vector				direction;
	SDL_Color				color;
	int						(*is_in_light)();
	void					(*get_ray_vect)();
}							t_parallel_light;

/*
** spotlight hérite de light
*/
typedef struct				s_spotlight
{
	const t_light_type		type;
	t_vector				direction;
	SDL_Color				color;
	int						(*is_in_light)();
	void					(*get_ray_vect)();
	t_dot					origin;
	double					aperture;
}							t_spotlight;

/*
** orb_light hérite de spotlight /!\ ne pas ajouter de champs, le constructeur
**                                   actuel ne le permet pas. /!\
*/
typedef struct				s_orb_light
{
	const t_light_type		type;
	t_vector				direction;
	SDL_Color				color;
	int						(*is_in_light)();
	void					(*get_ray_vect)();
	t_dot					origin;
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


typedef struct				s_parequation
{
	t_vector				vc;
	t_vector				vd;
}							t_parequation;

typedef struct				s_ray
{
	t_parequation			equ;
	t_dot					inter;
	t_vector				normal;
	SDL_Color				color;
}							t_ray;

#endif