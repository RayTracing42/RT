/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loading_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/22 16:05:02 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_loadingbar	new_loading_bar()
{
	t_loadingbar	lb;
	SDL_Surface		*tmp;

	lb = (t_loadingbar){NULL, NULL, NULL, 0, 0};
	tmp = NULL;
	if(!(lb.window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									WIN_WIDTH, WIN_HEIGHT,
									SDL_WINDOW_SHOWN)) ||
		!(lb.renderer = SDL_CreateRenderer(lb.window, -1,
											SDL_RENDERER_ACCELERATED)) ||
		!(tmp = SDL_LoadBMP("resources/loading.bmp")) ||
		!(lb.loadingtexture =
			SDL_CreateTextureFromSurface(lb.renderer, tmp)))
		exit_custom_error("rt : Erreur SDL2 : ", (char*)SDL_GetError());
	SDL_FreeSurface(tmp);
	return (lb);
}

void			destroy_loading_bar(t_loadingbar lb)
{
	SDL_DestroyTexture(lb.loadingtexture);
	SDL_DestroyRenderer(lb.renderer);
	SDL_DestroyWindow(lb.window);
}

void			update_loading_bar(t_loadingbar *lb)
{
	SDL_Rect		dim;
	const double	p = ((double)lb->val) /
						((get_sdl_core()->width * get_sdl_core()->height));

	if (lb->val >= lb->old + LB)
	{
		lb->old = lb->val;
		dim = (SDL_Rect){0, WIN_HEIGHT - 20, WIN_WIDTH * p, 20};
		SDL_RenderCopy(lb->renderer, lb->loadingtexture, NULL, NULL);
		SDL_SetRenderDrawColor(lb->renderer, 180, 180, 180, 255);
		SDL_RenderFillRect(lb->renderer, &dim);
		SDL_RenderPresent(lb->renderer);
	}
}
