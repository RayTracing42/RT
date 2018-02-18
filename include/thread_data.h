/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_data.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 13:32:58 by llellouc          #+#    #+#             */
/*   Updated: 2018/02/18 20:11:34 by edescoin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREAD_DATA_H
# define THREAD_DATA_H
# include "structures.h"

t_thread_data	*init_thread_array(t_scene *scn, int nb_thread);
t_mutexes		*get_mutexes();

#endif
