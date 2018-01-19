#include "rt.h"

void		refresh_win_effect(int (*f)())
{
	SDL_SetRenderTarget(get_sdl_core()->renderer, NULL);
	SDL_RenderCopy(get_sdl_core()->renderer, get_sdl_core()->target, NULL, NULL);
  f();
	SDL_RenderPresent(get_sdl_core()->renderer);
	SDL_SetRenderTarget(get_sdl_core()->renderer, get_sdl_core()->target);
}
