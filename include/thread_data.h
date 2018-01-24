/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llellouc <llellouc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:32:58 by llellouc          #+#    #+#             */
/*   Updated: 2018/01/24 13:36:53 by shiro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_DATA_h
#define THREAD_DATA_h
#include "structures.h"

t_thread_data	*init_thread_array(t_scene *scn, int nb_thread);
t_mutexes		*get_mutexes();

#endif
