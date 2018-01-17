/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 17:10:36 by edescoin          #+#    #+#             */
/*   Updated: 2017/09/05 23:50:23 by fcecilie         ###   ########.fr       */
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
void		put_pixel(int x, int y, SDL_Color *color);
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

int		gray(void);
void		apply_gray(SDL_Surface *screen, int x, int y);

int		sepia(void);
void		apply_sepia(SDL_Surface *screen, int x, int y);

int		lofi(void);
void		apply_lofi(SDL_Surface *screen, int x, int y);

int anaglyph(void);
void		apply_anaglyph(SDL_Surface *screen, int x, int y);

int		negative(void);
void		apply_negative(SDL_Surface *screen, int x, int y);

int		pop(void);
void		apply_pop(SDL_Surface *screen, int x, int y);

int		noise(void);
void		apply_noise(SDL_Surface *screen, int x, int y);

t_blur 	surrounding_pixels(SDL_Surface *screen, int x, int y);
int		laplacian(void);
void		apply_laplacian(SDL_Surface *screen, int x, int y);

int		prewitt(void);
void		apply_prewitt(SDL_Surface *screen, int x, int y);

int		bwnoise(void);
void		apply_bwnoise(SDL_Surface *screen, int x, int y);

int		duotone(SDL_Color col1, SDL_Color col2);
void		apply_duotone(SDL_Surface *screen, int x, int y, t_duotone t);

void		refresh_win_effect(int (*f)());

#endif
