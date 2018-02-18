# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/18 18:41:12 by edescoin          #+#    #+#              #
#    Updated: 2018/02/18 18:41:59 by edescoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = rt

SRC_DIR = src
LIB_DIR = libraries
INCLUDE_DIR = include

LFT_PATH = "$$(pwd)/libraries/libft"
SDL_PATH = "$$(pwd)/libraries/SDL"

LFT_INCLUDE = $(LFT_PATH)/includes

SRC = box.c camera.c cone.c cylinder.c equations.c events.c get_interval.c \
graphics.c hyperboloid.c intersections.c key_functions.c light.c \
light_shading.c limit2.c limit.c list_ray.c main.c matrix.c matrix_ops2.c \
matrix_ops.c matrix_transformations.c negative_obj.c object_light.c objects.c \
orb_light.c parallel_light.c parsing.c parsing_camera.c parsing_lights.c \
parsing_limit.c parsing_negative_obj.c parsing_objects.c parsing_scene.c \
parsing_tools.c parsing_transformations.c plane.c reflect_refract_tree.c \
reflexion.c refraction.c refract_list.c rendering.c scanning.c scene.c \
scene_lights.c scene_objs.c shadows.c sphere.c spotlight.c thread_data.c \
triangle.c utils.c vectors2.c vectors.c vectors_transformations.c view_plane.c \
effect_blur.c antialiasing.c effect_anaglyph.c effect_bwnoise.c effect_duotone.c \
effect_gray.c effect_laplacian.c effect_lofi.c effect_negative.c effect_noise.c \
effect_pop.c effect_prewitt.c effect_sepia.c effect_utils.c effect_blur.c perlin.c \
pixel_utils.c screenshot.c effect_cartoon.c effect_motionblur.c

SRC:= $(addprefix $(SRC_DIR)/, $(SRC))
OBJ = $(SRC:.c=.o)

LFT = -lft -lm
SDL = `$(SDL_PATH)/build/bin/sdl2-config --cflags --libs`


all: libft sdl $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $^ $(SDL) -L $(LIB_DIR) $(LFT) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -I $(INCLUDE_DIR) -o $@

libft:
	make -C $(LFT_PATH)
	ln -fs $(LFT_PATH)/libft.a $(LIB_DIR)
	ln -fs $(LFT_INCLUDE)/libft.h $(INCLUDE_DIR)

sdl:
	if [ ! -e $(SDL_PATH)/build ]; then mkdir $(SDL_PATH)/build; \
	cd $(SDL_PATH) && ./configure -q --prefix=$$(pwd)/build && make && make install; \
	cd ../..; \
	ln -fs $(SDL_PATH)/build/lib/libSDL2.a $(LIB_DIR); \
	ln -fs $(SDL_PATH)/build/include/SDL2 $(INCLUDE_DIR); \
	fi

clean:
	rm -rf $(OBJ)
	make clean -C $(LFT_PATH)
	rm -rf $(INCLUDE_DIR)/libft.h
	rm -rf $(LIB_DIR)/libft.a


fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LFT_PATH)
	rm -rf $(SDL_PATH)/build
	rm -rf $(INCLUDE_DIR)/SDL2
	rm -rf $(LIB_DIR)/libSDL2.a

re: fclean all

debug: $(SRC_DIR)/*.c
	$(CC) $(CFLAGS) -g -I $(INCLUDE_DIR) $^ $(SDL) -L $(LIB_DIR) $(LFT) -o $@
