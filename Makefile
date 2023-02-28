NAME				= philo
SRC_DIR				= srcs
OBJ_DIR				= objs
H_DIR				= incs
SRC_NAME			= utils.c philosopher.c check_params.c exit.c
INCS_NAME			= philosophers.h


OBJ_NAME			= $(SRC_NAME:%.c=%.o)

SRC 				= $(addprefix $(SRC_DIR)/,$(SRC_NAME))
OBJ 				= $(addprefix $(OBJ_DIR)/,$(OBJ_NAME))

INCS				= $(addprefix $(H_DIR)/,$(INCS_NAME))

####Compil####

CC 		= gcc
CFLAGS 	= -Wall -Wextra -Werror

#####LIBS#####

CH_FLAG			= -Iincs

### DEBUG ####
D = 0

ifeq ($(D), 1)
	CC += -fsanitize=address -g3
	MODE = printf %b "\033[0;31m MODE DEBUG SANITIZE \033[0m"
endif
ifneq ($(D), 1)
	MODE = printf %b "\033[0;31m MODE RELEASE \033[0m"
endif

## Rules ##

all:		$(NAME)

$(NAME):	$(OBJ)
	@$(CC) $^ -o $(NAME) $(CFLAGS) $(CH_FLAG)
	@printf %b	"\n"
	@printf %b  "\033[1;35m-[$(NAME)]__Edit/Create .o in \033[0m  \033[0;32m[OK]\033[0m\n"
	@printf %b  "\r"
	@$(MODE)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(INCS)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(CH_FLAG) -o $@ -c $<
	@printf %b "-\033[1;35m[$(NAME)]\033[0m__Compiling \033[1;92m$<\033[0m in \033[1;92m$@\033[0m..."
	@printf "\r"

clean:
	@rm -rf $(OBJ)
	@printf %b  "-\033[1;33m[$(NAME)]__Remove objs file  \033[0m  \".o\"         \033[0;32m [OK] \033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf %b  "-\033[1;33m[$(NAME)]__Remove \033[0m             \"$(NAME)\"    \033[0;32m [OK] \033[0m\n"

re: fclean all

.PHONY: all clean fclean re bonus