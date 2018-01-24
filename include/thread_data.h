//
//  thread_data.h
//  RT
//
//  Created by léo LELLOUCHE on 20/01/2018.
//  Copyright © 2018 léo LELLOUCHE. All rights reserved.
//

#ifndef thread_data_h
#define thread_data_h
#include "structures.h"

t_thread_data *init_thread_array(t_scene *scn, int nb_thread);
t_mutexes	*get_mutexes();

#endif /* thread_data_h */