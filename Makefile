# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/19 12:13:48 by thzeribi          #+#    #+#              #
#    Updated: 2026/02/19 12:29:58 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                   CONFIG                                     #
################################################################################

ifndef VERBOSE
        MAKEFLAGS += --no-print-directory --silent
endif

NAME            := fractol
PROJECT_NAME    := Fractol

################################################################################
#                                  SOURCES                                     #
################################################################################
SOURCES_FOLDER  := ./srcs/
INCLUDES_FOLDER := ./privates/
OBJECTS_FOLDER  := ./objs/
LIBFT_FOLDER    := ./libft/
MLX_FOLDER      := minilibx-linux

COMMON_SOURCES := \
                main.c \
                mlx/init/mlx_init.c \
                mlx/init/hook_init.c \
                mlx/img/img_utils.c \
                mlx/end/mlx_end.c \
                mlx/event/key_event.c \
                mlx/event/mouse_event.c \
                mlx/event/julia_mouse.c \
                utils/usage.c \
                utils/colors.c \
                utils/palette.c \
                utils/exit_case.c \
								utils/math.c \
                utils/debug_overlay.c \
                utils/debug_draw.c \
                utils/space_palette.c \
                sets/mandelbrot/mandelbrot_core.c \
                sets/burning_ship/burning_ship_core.c \
                sets/julia/julia_core.c \
                sets/buddhabrot/buddhabrot_core.c \
                sets/phoenix/phoenix_core.c \

MANDATORY_SOURCES := \
                init_set.c \
                sets/mandelbrot/mandelbrot.c \
                sets/burning_ship/burning_ship.c \
                sets/julia/julia.c \
                sets/buddhabrot/buddhabrot.c \
                sets/phoenix/phoenix.c \

BONUS_SOURCES := \
                init_set_bonus.c \
                bonus/threads.c \
                bonus/thread_affinity.c \
                bonus/simd_utils.c \
                bonus/simd_mandelbrot.c \
                bonus/simd_other.c \
								sets/mandelbrot/mandelbrot_bonus.c \
								sets/burning_ship/burning_ship_bonus.c \
								sets/julia/julia_bonus.c \
								sets/buddhabrot/buddhabrot_bonus.c \
								sets/phoenix/phoenix_bonus.c \

################################################################################
#                                   FLAGS                                      #
################################################################################

CFLAGS      := -Wall -Wextra -Werror -MMD -O3 -march=native
CC          := cc
LDFLAGS     := -L $(MLX_FOLDER) -lm -lmlx -lXext -lX11
DBG         := 0
BNS         := 0

NPROCS      := $(shell nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 1)
MAKEFLAGS   += -j$(NPROCS)

INCLUDES    := -I$(INCLUDES_FOLDER) -I$(MLX_FOLDER)

################################################################################
#                                   LOGICS                                     #
################################################################################

ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
        INCLUDES += -I$(LIBFT_FOLDER)includes
        LDFLAGS  += -L $(LIBFT_FOLDER) -lft
endif

ifneq (,$(wildcard ./.BNS.*))
        ifeq ($(findstring $(MAKECMDGOALS), re),)
                FILE := $(shell find . -name ".BNS.*" -type f)
                BNS := $(shell echo $(FILE) | rev | cut -d "." -f1 | rev )
        endif
endif

ifeq ($(BNS), 1)
        SOURCES := $(COMMON_SOURCES) $(BONUS_SOURCES)
        CFLAGS  += -pthread -DBONUS
        LDFLAGS += -lpthread
        BONUS   := $(BNS)
else
        SOURCES := $(COMMON_SOURCES) $(MANDATORY_SOURCES)
        BONUS   := 0
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

################################################################################
#                                   OBJECTS                                    #
################################################################################

OBJECTS   := $(SOURCES:.c=.o)
OBJECTS   := $(addprefix $(OBJECTS_FOLDER),$(OBJECTS))
SOURCES   := $(addprefix $(SOURCES_FOLDER),$(SOURCES))
DEPS      := $(OBJECTS:.o=.d)

################################################################################
#                                   COLORS                                     #
################################################################################

NO_COLOR      := \033[38;5;15m
OK_COLOR      := \033[38;5;2m
ERROR_COLOR   := \033[38;5;1m
WARN_COLOR    := \033[38;5;3m
SILENT_COLOR  := \033[38;5;245m
INFO_COLOR    := \033[38;5;140m
OBJ_COLOR     := \033[0;36m

################################################################################
#                                   RULES                                      #
################################################################################


all: header
	+$(MAKE) setup_mlx
	+$(MAKE) makelib
	+$(MAKE) $(NAME)

$(NAME): $(OBJECTS)
	printf "\t\t$(NO_COLOR)All objects for $(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)where successfully created.\n"
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^ $(LDFLAGS)
	printf "%-50s \r"
	printf "\t\t$(INFO_COLOR)$(NAME)$(NO_COLOR) successfully compiled. $(OK_COLOR)✓$(NO_COLOR)\n"

bonus: header
	+$(MAKE) setup_mlx
	+$(MAKE) makelib
	@if [ ! -f .BNS.1 ]; then rm -f .BNS.*; touch .BNS.1; fi
	+$(MAKE) $(NAME)

.BNS.$(BONUS):
	rm -f .BNS.*
	touch $@

.DBG.$(DEBUG):
	rm -f .DBG.*
	touch $@

-include $(DEPS)

$(OBJECTS_FOLDER)%.o: $(SOURCES_FOLDER)%.c .DBG.$(DEBUG) .BNS.$(BONUS)
	mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	printf "%-50s \r"
	printf "\t\t\t$(NO_COLOR)Creating $(INFO_COLOR)%-30s $(OK_COLOR)✓$(NO_COLOR)\r" "$@"

$(MLX_FOLDER)/libmlx.a:
	+$(MAKE) -C $(MLX_FOLDER) all --quiet

makelib: $(MLX_FOLDER)/libmlx.a
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	+$(MAKE) -C $(LIBFT_FOLDER)
endif

config:
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	+$(MAKE) -C $(LIBFT_FOLDER) config
	rm -rf $(OBJECTS_FOLDER)
	rm -f $(NAME)
	+$(MAKE) all
else
	printf "\n$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)has no libft configured$(NO_COLOR).\n\n"
endif

clean: header
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	+$(MAKE) -C $(LIBFT_FOLDER) clean
endif
ifneq "$(wildcard $(MLX_FOLDER) )" ""
	+$(MAKE) -C $(MLX_FOLDER) clean --quiet
endif
	rm -f $(OBJECTS)
	rm -rf $(OBJECTS_FOLDER)

fclean: clean
ifneq "$(wildcard $(LIBFT_FOLDER) )" ""
	+$(MAKE) -C $(LIBFT_FOLDER) fclean
endif
ifneq "$(wildcard $(MLX_FOLDER) )" ""
	rm -rf $(MLX_FOLDER)
endif
	rm -f $(NAME)
	rm -f .DBG.* .BNS.*
	printf "\t\t$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)Removed $(INFO_COLOR)$(NAME)$(NO_COLOR).\n"

re:
	+$(MAKE) fclean
	+$(MAKE) all

.PHONY: all re clean fclean makelib config bonus

-include ./Templates/header.mk ./Templates/asan.mk ./Templates/mallocator.mk \
  ./Templates/debug.mk ./Templates/setup_mlx.mk
-include ./Templates/norm.mk ./Templates/coffee.mk
