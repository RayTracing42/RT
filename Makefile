# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/05 23:28:25 by fcecilie          #+#    #+#              #
#    Updated: 2017/09/06 00:52:51 by fcecilie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -Wall -Wextra -Werror -Ofast
MAKE=/usr/bin/make
NAME=rtv1

OBJ_DIR=obj
SRC_DIR=src
LIB_DIR=lib
INCLUDE_DIR=include

FT_PATH=$$(pwd)/libft
SDL_PATH=$$(pwd)/SDL2

SRCS =	main.c \

OBJS=$(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
	LIBS=-lft -lm
	LSDL2=`$(SDL_PATH)/SDL2/build/bin/sdl2-config --cflags --libs`

.PHONY: all clean fclean re libft sdl debug-linux debug-mac


all: libft sdl $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	@echo "=================================================="
	@echo
	@echo "Objects generation : ""\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                 Building $@..."
	@echo "--------------------------------------------------"
	$(CC) $(CFLAGS) $^ -o $@ $(LSDL2) -L$(LIB_DIR) $(LIBS)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "=================================================="

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $^ -o $@ -c -I$(INCLUDE_DIR)

$(LIB_DIR):
	@mkdir $@

libft: $(LIB_DIR)
	@echo "                Compiling libft..."
	@echo "--------------------------------------------------------------------\
		------------"
	$(MAKE) -C $(FT_PATH)
	@echo
	@echo "                Creating symlinks..."
	@echo "--------------------------------------------------------------------\
		------------"
	ln -fs $(FT_PATH)/libft.a $(LIB_DIR)
	ln -fs $(FT_PATH)/libft.h $(INCLUDE_DIR)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


sdl: $(LIB_DIR)
	@echo "         Installing SDL2 in $(SDL_PATH)"
	@echo "--------------------------------------------------------------------\
		------------"
	@if [ ! -e $(SDL_PATH)/bin ]; then\
		mkdir $(SDL_PATH)/bin && echo "mkdir $(SDL_PATH)/bin";\
		fi
	cd SDL2 && CC=./build-scripts/gcc-fat.sh ./configure -q \
		--prefix=$(SDL_PATH)/bin && make && make install
	@echo
	@echo "               Creating symlinks..."
	@echo "--------------------------------------------------------------------\
		------------"
	ln -fs $(SDL_PATH)/SDL2/build/lib/libSDL2.a $(LIB_DIR)
	ln -fs $(SDL_PATH)/SDL2/build/include/SDL2 $(INCLUDE_DIR)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


clean:
	@echo "                Cleaning libft..."
	@echo "--------------------------------------------------------------------\
		------------"
	$(MAKE) clean -C $(FT_PATH)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                Removing objects..."
	@echo "--------------------------------------------------------------------\
		------------"
	rm -f $(OBJS)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


fclean: clean
	@echo "                 Removing $(NAME)..."
	@echo "--------------------------------------------------------------------\
		------------"
	rm -f $(NAME)
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                Removing libft..."
	@echo "--------------------------------------------------------------------\
		------------"
	rm -f $(FT_PATH)/libft.a
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo
	@echo "                Removing symlinks"
	@echo "--------------------------------------------------"
	rm -f $(LIB_DIR)/*
	@echo
	@echo "\x1B[38;5;40m""Done.""\x1B[0m"
	@echo


re: fclean all

debug-linux: $(OBJS)
	$(CC) $(CFLAGS) $^ -L$(LIB_DIR) $(LIBS) -lSDL2
	$(MAKE) clean

debug-mac: $(OBJS)
	$(CC) $(CFLAGS) $^ `$(SDL_PATH)/SDL2/build/bin/sdl2-config --cflags --libs`\
		-L$(LIB_DIR) -lft -lm
