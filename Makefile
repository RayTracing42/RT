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

SRC_DIR = sources
LIB_DIR = libraries
INCLUDE_DIR = includes

LFT_PATH = $$(pwd)/libraries/libft
SDL_PATH = $$(pwd)/libraries/SDL

LFT_INCLUDE = $(LFT_PATH)/includes

SRC = main.c cone.c events.c key_functions.c objects.c parallel_light.c \
	  scanning.c spotlight.c cylinder.c graphics.c light.c objects2.c \
	  orb_light.c plane.c sphere.c view_plane.c utils.c matrice_rotation.c
	
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

test:
