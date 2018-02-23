/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2018/02/23 11:43:14 by edescoin         ###   ########.fr       */
=======
/*   Updated: 2018/02/23 11:48:43 by joinacio         ###   ########.fr       */
>>>>>>> ff05d92eb19ea628e54fbd98a8c8b16d965f5bb2
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_loadingbar	new_loading_bar(void)
{
	t_loadingbar	lb;
	SDL_Surface		*tmp;

	lb = (t_loadingbar){NULL, 0, 0};
	tmp = NULL;
	if (!(tmp = SDL_LoadBMP("resources/loading.bmp")) ||
<<<<<<< HEAD
		!(lb.loadingtexture =
=======
		!(lb.loadingtexture = \
>>>>>>> ff05d92eb19ea628e54fbd98a8c8b16d965f5bb2
			SDL_CreateTextureFromSurface(get_sdl_core()->renderer, tmp)))
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	SDL_FreeSurface(tmp);
	return (lb);
}

void			destroy_loading_bar(t_loadingbar lb)
{
	SDL_DestroyTexture(lb.loadingtexture);
}

void			update_loading_bar(t_loadingbar *lb)
{
	SDL_Rect		dim;
	const double	p;

	p = ((double)lb->val) / ((get_sdl_core()->width * get_sdl_core()->height));
	if (lb->val >= lb->old + LB)
	{
		lb->old = lb->val;
		dim = (SDL_Rect){0, WIN_HEIGHT - 20, WIN_WIDTH * p, 20};
		SDL_SetRenderDrawColor(get_sdl_core()->renderer, 180, 180, 180, 255);
		SDL_SetRenderTarget(get_sdl_core()->renderer, NULL);
<<<<<<< HEAD
		SDL_RenderCopy(get_sdl_core()->renderer, lb->loadingtexture, NULL,
					NULL);
=======
		SDL_RenderCopy(get_sdl_core()->renderer, \
				lb->loadingtexture, NULL, NULL);
>>>>>>> ff05d92eb19ea628e54fbd98a8c8b16d965f5bb2
		SDL_RenderFillRect(get_sdl_core()->renderer, &dim);
		SDL_RenderPresent(get_sdl_core()->renderer);
		SDL_SetRenderTarget(get_sdl_core()->renderer, get_sdl_core()->target);
	}
}
