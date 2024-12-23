# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/19 12:13:48 by thzeribi          #+#    #+#              #
#    Updated: 2024/02/23 10:13:22 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                   CONFIG                                     #
################################################################################

ifndef VERBOSE
	MAKEFLAGS += --no-print-directory --silent
endif

NAME				:=	fractol
PROJECT_NAME		:=	Fractol

################################################################################
#                                  SOURCES                                     #
################################################################################
SOURCES_FOLDER		:=	./srcs/
INCLUDES_FOLDER		:=	./privates/
OBJECTS_FOLDER		:=	./objs/
LIBFT_FOLDER		:=	./libft/

SOURCES := \
		main.c \
		\
		mlx/init/mlx_init.c \
		mlx/init/hook_init.c \
		mlx/img/img_utils.c \
		mlx/end/mlx_end.c \
		mlx/event/key_event.c \
		mlx/event/mouse_event.c \
		\
		sets/mandelbrot.c \
		sets/burning_ship.c \
		\
		utils/usage.c \
		utils/colors.c \
		utils/exit_case.c \

BONUS_SOURCES := \
		sets/mandelbrot_bonus.c \
		sets/burning_ship_bonus.c \

################################################################################
#                                   MLX                                        #
################################################################################

PATH_MLX	:= minilibx-linux

################################################################################
#                                  FLAGS                                       #
################################################################################

CFLAGS			:=	-Wall -Wextra -Werror -MMD
CC				:=	cc
LDFLAGS			:=	-L $(PATH_MLX) \
					-lm -lmlx -lXext -lX11 -lpthread
DBG				:=	0
BNS				:=	0

INCLUDES		:= -I$(INCLUDES_FOLDER) -I$(PATH_MLX)

ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	INCLUDES += -I$(LIBFT_FOLDER)includes
	LDFLAGS  += -L $(LIBFT_FOLDER) -lft
endif

ifneq (,$(wildcard ./.DBG.*))
	ifeq ($(findstring $(MAKECMDGOALS), re),)
		FILE := $(shell find . -name ".DBG.*" -type f)
		DBG := $(shell echo $(FILE) | rev | cut -d "." -f1 | rev )
	endif
endif

ifeq ($(DBG), 1)
	CFLAGS += -g3 -fsanitize=address -fsanitize=undefined
	DEBUG := $(DBG)
else ifeq ($(DBG), 2)
	CFLAGS += -g3
	DEBUG := $(DBG)
else
	DEBUG := 0
endif

ifneq (,$(wildcard ./.BNS.*))
	ifeq ($(findstring $(MAKECMDGOALS), re),)
		FILE := $(shell find . -name ".BNS.*" -type f)
		BNS := $(shell echo $(FILE) | rev | cut -d "." -f1 | rev )
	endif
endif

ifeq ($(BNS), 1)
	SOURCES += $(BONUS_SOURCES)
	CFLAGS += -pthread -DBONUS -O0
	BONUS := $(BNS)
else
	BONUS := 0
endif

################################################################################
#                                  OBJETS                                      #
################################################################################

OBJECTS		:=	$(SOURCES:.c=.o)
OBJECTS		:=	$(addprefix $(OBJECTS_FOLDER),$(OBJECTS))
SOURCES		:=	$(addprefix $(SOURCES_FOLDER),$(SOURCES))
DEPS		:=	$(OBJECTS:.o=.d)


################################################################################
#                                 COLORS                                       #
################################################################################

NO_COLOR 		:=	\033[38;5;15m
OK_COLOR		:=	\033[38;5;2m
ERROR_COLOR		:=	\033[38;5;1m
WARN_COLOR		:=	\033[38;5;3m
SILENT_COLOR	:=	\033[38;5;245m
INFO_COLOR		:=	\033[38;5;140m
OBJ_COLOR		:=	\033[0;36m

################################################################################
#                                 RULES                                        #
################################################################################

all: header makelib $(NAME)

$(NAME): $(OBJECTS)
	printf "\t\t$(NO_COLOR)All objects for $(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)where successfully created.\n"
	printf "\t\t$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)Removed all objects$(NO_COLOR).\n"
	printf "\n\t\t$(NO_COLOR)-------- $(INFO_COLOR) Start Compilation for ${PROJECT_NAME} $(NO_COLOR)--------\n"	
	# $(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJECTS) $(LDFLAGS) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	printf "%-50s \r"
	printf "\t\t$(INFO_COLOR)$(NAME)$(NO_COLOR) successfully compiled. $(OK_COLOR)✓$(NO_COLOR)\n"

-include $(DEPS)
$(OBJECTS_FOLDER)%.o: $(SOURCES_FOLDER)%.c .DBG.$(DEBUG) .BNS.$(BONUS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf "%-50s \r"
	printf "\t\t\t$(NO_COLOR)Creating $(INFO_COLOR)%-30s $(OK_COLOR)✓$(NO_COLOR)\r" "$@"

$(PATH_MLX)/libmlx.a:
	$(MAKE) -C $(PATH_MLX) all --quiet
	printf "\033[32;1m%s OK%40.40s\n\033[0m" $(PATH_MLX) ""

makelib: $(PATH_MLX)/libmlx.a
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	$(MAKE) -C $(LIBFT_FOLDER)
endif

config:
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	$(MAKE) -C $(LIBFT_FOLDER) config
	rm -rf $(OBJECTS_FOLDER)
	rm -f $(NAME)
	$(MAKE) all
else
	printf "\n$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)has no libft configured$(NO_COLOR).\n\n"
endif

clean: header
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	$(MAKE) -C $(LIBFT_FOLDER) clean
endif
	rm -f $(OBJECTS)

fclean: clean
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	$(MAKE) -C $(LIBFT_FOLDER) fclean
	printf "\t\t$(INFO_COLOR)LibFt $(NO_COLOR)Removed $(INFO_COLOR)Libft$(NO_COLOR).\n"
endif
	$(MAKE) -C $(PATH_MLX) clean --quiet --jobs
	rm -f $(NAME)
	rm -rf $(OBJECTS_FOLDER)
	rm -f .DBG.* .BNS.*
	printf "\t\t$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)Removed $(INFO_COLOR)$(NAME)$(NO_COLOR).\n"

re: fclean all

.PHONY: all re clean fclean makelib config

-include ./Templates/header.mk ./Templates/asan.mk ./Templates/mallocator.mk \
	./Templates/debug.mk ./Templates/bonus.mk
-include ./Templates/norm.mk ./Templates/coffee.mk
