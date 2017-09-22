CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=libft.a
SRC= ft_angles.c errors.c ft_putstr.c ft_putstr_fd.c ft_strlen.c
OBJ= $(SRC:.c=.o)
BLANK="\x1B[0m"
DGREEN="\x1B[38;5;28m"
GREEN="\x1B[38;5;40m"
LGREEN="\x1B[38;5;119m"
LLGREEN="\x1B[38;5;193m"
WHITE="\x1B[37m"
DBLUE="\x1B[38;5;19m"
BLUE="\x1B[38;5;21m"
LBLUE="\x1B[38;5;27m"
LLBLUE="\x1B[38;5;81m"


.PHONY: all clean fclean re header it_fabulous

all: $(NAME)

$(NAME): $(OBJ)
	@ar qcs $@ $^

$(OBJ): $(SRC)
	@$(CC) -c $^ $(CFLAGS)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

header:
	clear
	@for i in {1..26} ; do echo $(DGREEN)'<>'$(DBLUE)'-' | tr -d "\n"; done
	@echo $(DGREEN)'<>'
	@echo $(GREEN)'*                                                                            '$(WHITE)'|'$(GREEN)' *'
	@echo $(DBLUE)'|          '$(DGREEN)'/####/         /####/  /########\     /###########/  /###########'$(WHITE)'- -'$(DBLUE)'|'
	@echo $(DBLUE)'|         '$(DGREEN)'/####/         /####/  /#########/    /###########/  /############/'$(WHITE)'|'$(DBLUE)' |'
	@echo $(DBLUE)'|        '$(DGREEN)'/####/         /####/  /####   ##/    /###########/  /############/   '$(DBLUE)'|'
	@echo $(BLUE)'|       '$(GREEN)'/####/         /####/  /####   ##/    /####/             /####/'$(BLUE)'        |'
	@echo $(LBLUE)'|      '$(LGREEN)'/####/         /####/  /#########/    /#########/        /####/'$(LBLUE)'         |'
	@echo $(LLBLUE)'|     '$(LLGREEN)'/####/         /####/  /##########\   /#########/        /####/'$(LLBLUE)'          |'
	@echo $(LBLUE)'|    '$(LGREEN)'/####/         /####/  /####   ####/  /####/             /####/'$(LBLUE)'           |'
	@echo $(BLUE)'|   '$(GREEN)'/###########/  /####/  /####   ####/  /####/             /####/'$(BLUE)'            |'
	@echo $(DBLUE)'| '$(WHITE)'|'$(DGREEN)'/###########/  /####/  /###########/  /####/             /####/'$(DBLUE)'             |'
	@echo $(DBLUE)'|'$(WHITE)'- -'$(DGREEN)'##########/  /####/  /###########/  /####/             /####/'$(DBLUE)'              |'
	@echo $(GREEN)'* '$(WHITE)'|'$(GREEN)'                                                                            *'
	@for i in {1..26} ; do echo $(DGREEN)'<>'$(DBLUE)'-' | tr -d "\n"; done
	@echo $(DGREEN)'<>'
	@echo

it_fabulous: header all clean
	@echo $(WHITE)'<' | tr -d '\n'
	@for i in {17..21} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {27..22} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {28..33} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {39..34} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {40..45} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {51..46} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@echo $(WHITE)'['$(GREEN)' DONE '$(WHITE)']' | tr -d '\n'
	@for i in {46..51} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {45..40} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {34..39} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {33..28} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {22..27} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {21..17} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@echo $(WHITE)'>'
	@echo
	@echo '    List of files added to the library :'
	@echo $(LLGREEN)'    ------------------------------------'$(BLANK)
	@echo
	@echo $(SRC) | tr ' ' '\n' | sed 's/^/    - /'
	@echo $(WHITE)'<' | tr -d '\n'
	@for i in {17..21} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {27..22} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {28..33} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {39..34} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {40..45} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {51..46} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {1..8} ; do echo = | tr -d '\n'; done
	@for i in {46..51} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {45..40} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {34..39} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {33..28} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {22..27} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@for i in {21..17} ; do echo "\x1B[38;5;"$$i"m"= | tr -d '\n'; done
	@echo $(WHITE)'>'
