/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiro <shiro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:38:08 by shiro             #+#    #+#             */
/*   Updated: 2018/01/24 14:21:19 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERING_H
#define RENDERING_H
#include "structures.h"

void		delete_pxl_queues();
t_pxl_queue	**get_pxl_queue(int n);
void		put_pixel(int x, int y, SDL_Color *color);
int			rendering_thread(void* data);

#endif
