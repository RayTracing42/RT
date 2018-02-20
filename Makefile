# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edescoin <edescoin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/02/18 18:41:12 by edescoin          #+#    #+#              #
#    Updated: 2018/02/20 18:57:59 by edescoin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

SRC_DIR = src
LIB_DIR = libraries
INCLUDE_DIR = include

LFT_PATH = "$$(pwd)/libraries/libft"
SDL_PATH = "$$(pwd)/libraries/SDL"

LFT_INCLUDE = $(LFT_PATH)/includes

COLOR = \0033[1;35m

## List of Directories

INC_DIR = include
OBJ_DIR = objs
SRC_DIR = src
LIB_DIR = libraries/libft

## Compilating Utilities

FLAGS = -Wall -Wextra -Werror -D_REENTRANT -Ofast
INC = $(INC_DIR:%=-I./%)
LIB = -L$(LIB_DIR) -lft
#INC_SDL2 = `sdl2-config --cflags`
INC_SDL2 = -I./SDL2/include -D_THREAD_SAFE
#SDL2 = `sdl2-config --libs`
SDL2 = `$(SDL_PATH)/build/bin/sdl2-config --cflags --libs`

CC = /usr/bin/clang $(FLAGS) $(INC)
MAKE = /usr/bin/make

## List of Functions

SRC_FT = antialiasing \
		 box \
		 box2 \
		 camera \
		 cone \
		 cylinder \
		 effect_anaglyph \
		 effect_blur \
		 effect_bwnoise \
		 effect_cartoon \
		 effect_duotone \
		 effect_gray \
		 effect_laplacian \
		 effect_lofi \
		 effect_motionblur \
		 effect_negative \
		 effect_noise \
		 effect_pop \
		 effect_prewitt \
		 effect_sepia \
		 effect_utils \
		 equations \
		 events \
		 graphics \
		 hyperboloid \
		 intersections \
		 intersections2 \
		 key_functions \
		 light \
		 light_shading \
		 limit \
		 limit2 \
		 list_ray \
		 main \
		 matrix \
		 matrix_ops \
		 matrix_ops2 \
		 matrix_ops3 \
		 matrix_transformations \
		 negative_obj \
		 object_light \
		 object_light2 \
		 objects \
		 orb_light \
		 parallel_light \
		 parsing \
		 parsing2 \
		 parsing_camera \
		 parsing_interval \
		 parsing_interval2 \
		 parsing_lights \
		 parsing_lights2 \
		 parsing_limit \
		 parsing_negative_obj \
		 parsing_objects \
		 parsing_objects2 \
		 parsing_scene \
		 parsing_textures \
		 parsing_textures2 \
		 parsing_tools \
		 parsing_transformations \
		 perlin \
		 pixel_utils \
		 plane \
		 reflect_refract_tree \
		 reflexion \
		 refract_list \
		 refraction \
		 rendering \
		 scanning \
		 scanning2 \
		 scene \
		 scene_lights \
		 scene_objs \
		 screenshot \
		 shadows \
		 shadows2 \
		 sphere \
		 spotlight \
		 textures \
		 textures2 \
		 thread_data \
		 triangle \
		 utils \
		 vectors \
		 vectors2 \
		 vectors_transformations \
		 view_plane \


## List of Utilities

OBJ = $(SRC_FT:%=$(OBJ_DIR)/%.o)
SRC = $(SRC_FT:%=$(SRC_DIR)/%.c)

## Rules of Makefile

all: sdl2 libft $(NAME)
	@echo "$(COLOR)$(NAME)\t\t\0033[1;30m[All OK]\0033[1;37m"

$(OBJ_DIR):
	@mkdir -p $@
	@echo "$(COLOR)Creating    : \0033[0;32m$@\0033[1;37m"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(INC_SDL2) -c $< -o $@
	@echo "$(COLOR)Compiling : \0033[0;32m$(@:$(OBJ_DIR)/%=%)\0033[1;37m"

$(NAME): $(OBJ_DIR) $(SRC)
	@$(MAKE) -j -s $(OBJ)
	@echo "$(COLOR)Objects\t\t\0033[0;32m[Created]\0033[1;37m"
	@$(MAKE) -j -s -C $(LIB_DIR)
	@$(CC) $(LIB) $(SDL2) $(OBJ) -o $@
	@echo "$(COLOR)$(NAME)\t\t\0033[0;32m[Created]\0033[1;37m"

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C $(LIB_DIR)
	@echo "$(COLOR)Objects\t\t\0033[0;31m[Deleted]\0033[1;37m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIB_DIR)
	@echo "$(COLOR)$(NAME)\t\t\0033[0;31m[Deleted]\0033[1;37m"

re: fclean all

norme:
	@norminette $(SRC) $(INC_DIR)/
	@$(MAKE) norme -C $(LIB_DIR)

sdl2_clean:
	@rm -rf ./SDL2

sdl2:
	@if ! [ -e ./SDL2 ]; then\
		curl -o SDL2 https://www.libsdl.org/release/SDL2-2.0.5.tar.gz;\
		gunzip -c SDL2 | tar xopf -;\
		rm -rf SDL2;\
		mv -f ./SDL2-2.0.5 ./SDL2;\
	fi
	(cd ./SDL2 && ./configure)
	(cd ./SDL2 && sed -i.bak 's/^\prefix =.*/\prefix = $$(srcdir)/' Makefile)
	(cd ./SDL2 && $(MAKE) && $(MAKE) install)

libft:
	@cd $(LFT_PATH) && $(MAKE)

.PHONY: all clean fclean re norme sdl2 sdl2_clean libft
