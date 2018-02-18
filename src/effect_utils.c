/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effect_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 09:27:44 by joinacio          #+#    #+#             */
/*   Updated: 2018/02/18 12:39:16 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		refresh_win_effect(int (*f)())
{
	SDL_SetRenderTarget(get_sdl_core()->renderer, NULL);
	SDL_RenderCopy(get_sdl_core()->renderer, get_sdl_core()->target, NULL, NULL);
  f();
	SDL_RenderPresent(get_sdl_core()->renderer);
	SDL_SetRenderTarget(get_sdl_core()->renderer, get_sdl_core()->target);
}
