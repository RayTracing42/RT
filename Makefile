# ============================================================================ #
#                                                                              #
#         fichier :   Makefile                                                 #
#                                                                              #
#         auteur  :   fcecilie                                                 #
#         adresse :   fcecilie@student.42.fr                                   #
#                                                                              #
# ============================================================================ #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = rt

SRC_DIR = src
LIB_DIR = libraries
INCLUDE_DIR = include

LFT_PATH = $$(pwd)/libraries/libft
SDL_PATH = $$(pwd)/libraries/SDL

LFT_INCLUDE = $(LFT_PATH)/includes

SRC = camera.c cone.c cylinder.c events.c graphics.c key_functions.c light.c \
light_shading.c main.c matrice_rotation.c objects.c objects2.c orb_light.c \
parallel_light.c plane.c reflexion.c refract_list.c refraction.c scanning.c \
scene.c scene_lights.c scene_objs.c shadows.c sphere.c spotlight.c tools.c \
utils.c vectors.c view_plane.c parsing.c parsing_tools.c parsing_camera.c \
parsing_scene.c parsing_lights.c parsing_objects.c parsing_transformations.c \
transformations.c matrix_ops.c matrix.c check_intersect.c limits.c

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

fclean: clean
	rm -rf $(NAME)
	make fclean -C $(LFT_PATH)
	rm -rf $(SDL_PATH)/build

re: fclean all

debug: $(SRC)
	$(CC) $(CFLAGS) -g -I $(INCLUDE_DIR) $(SRC) $(SDL) -L $(LIB_DIR) $(LFT) -o $@
