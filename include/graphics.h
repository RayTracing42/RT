/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:36 by edescoin          #+#    #+#             */
/*   Updated: 2018/01/24 13:39:00 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H
# include "structures.h"
# ifndef __APPLE__
#  include <SDL2/SDL.h>
# else
#  include "SDL2/SDL.h"
# endif

/*
** graphics.c
*/
void		delete_sdl_core();
Uint32		get_color(int r, int g, int b);
t_sdl_core	*get_sdl_core();
void		refresh_win();

/*
** screenshot.c
*/
int		ft_access(const char *path);
char	*screenshot_name(int num);
char	*name_screen(void);
int		screenshot(void);

/*
** blur_effect.c
*/
SDL_Color 	get_pixel_colors(SDL_Surface *screen, int x, int y);
SDL_Color		pixelaccess(SDL_Surface *s, int x, int y, SDL_Color curr);
SDL_Color 	blur_color_picker(t_blur c);
void		apply_blur(SDL_Surface *screen, int x, int y);
int		blur(void);

/*
** antialiasing.c
*/
SDL_Color			pixels_merger(SDL_Color pixel1, SDL_Color pixel2);
void		x4_antia(SDL_Surface *screen, int x, int y);
int		antia(void);

/*
** effect_gray.c
*/
int		gray(void);
void		apply_gray(SDL_Surface *screen, int x, int y);

/*
** effect_sepia.c
*/
int		sepia(void);
void		apply_sepia(SDL_Surface *screen, int x, int y);

/*
** effect_lofi.c
*/
int		lofi(void);
void		apply_lofi(SDL_Surface *screen, int x, int y);

/*
** effect_anaglyph.c
*/
int anaglyph(void);
void		apply_anaglyph(SDL_Surface *screen, int x, int y);

/*
** effect_negative.c
*/
int		negative(void);
void		apply_negative(SDL_Surface *screen, int x, int y);

/*
** effect_pop.c
*/
int		pop(void);
void		apply_pop(SDL_Surface *screen, int x, int y);

/*
** effect_noise.c
*/
int		noise(void);
void		apply_noise(SDL_Surface *screen, int x, int y);

/*
** effect_laplacian.c
*/
t_blur 	surrounding_pixels(SDL_Surface *screen, int x, int y);
int		laplacian(void);
void		apply_laplacian(SDL_Surface *screen, int x, int y);

/*
** effect_prewitt.c
*/
int		prewitt(void);
void		apply_prewitt(SDL_Surface *screen, int x, int y);

/*
** effect_bwnoise.c
*/
int		bwnoise(void);
void		apply_bwnoise(SDL_Surface *screen, int x, int y);

/*
** effect_duotone.c
*/
int		duotone(SDL_Color col1, SDL_Color col2);
void		apply_duotone(SDL_Surface *screen, int x, int y, t_duotone t);

/*
** pixel_utils.c
*/
int		set_color(unsigned char a, unsigned char r, \
		unsigned char v, unsigned char b);
void put_pixel32(SDL_Surface *surface, int x, int y, Uint32 colors);

/*
** perlin.c
*/
int 		rand_between(int min, int max);
int randbet255(int r, int c, int val);
void perlinmaker(t_perlin *p, int x, int y);
void		perlin_pinpin(int x, int y);

#endif
