# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 01:36:34 by brda-sil          #+#    #+#              #
#    Updated: 2022/06/30 02:18:46 by brda-sil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# config

ifeq ($(findstring bonus,$(MAKECMDGOALS)),bonus)
BONUS				:= 1
VERSION				:= 1.4.0
TARGET				:= philo_bonus
else
BONUS				:= 0
VERSION				:= 1.4.0
TARGET				:= philo
endif
CFLAGS				:= -Wall -Wextra -pthread
RM					:= rm -rf
CC					:= gcc
MAKE				:= make -C
$(eval export MAIN=1)

ifneq ($(PADDING),35)
PADDING				:= 35
endif

ifeq ($(DEBUG),)
CFLAGS				+= -Werror
else
CFLAGS				+= -g3
endif

ifneq ($(DEBUG_THREAD),)
CFLAGS				+= -g3 -fsanitize=thread
endif

# DIR
BIN_DIR				:= bin
ifeq ($(BONUS),1)
SRC_DIR				:= philo_bonus
OBJ_DIR				:= obj_bonus
else
SRC_DIR				:= philo
OBJ_DIR				:= obj
endif
OBJ_SUBDIR			:= $(sort $(shell find $(SRC_DIR) -type d | \
										sed 's|$(SRC_DIR)|$(OBJ_DIR)|g'))
INC_DIR				:= -Iincludes
TARGET				:= $(addprefix $(BIN_DIR)/,$(TARGET))

# SRC

ifeq ($(BONUS),1)
SRC_C				:= dataset/ft_free.c \
					   dataset/ft_init.c \
					   dataset/ft_parse.c \
					   debug/ft_debug.c \
					   philosophers.c \
					   time/ft_time.c \
					   utils/ft_atol.c \
					   utils/ft_error.c \
					   utils/ft_isnum.c
else
SRC_C				:= dataset/ft_free.c \
					   dataset/ft_init.c \
					   dataset/ft_parse.c \
					   debug/ft_debug.c \
					   life/ft_death.c \
					   life/ft_eat.c \
					   life/ft_sleep.c \
					   life/ft_solo.c \
					   life/ft_world.c \
					   philosophers.c \
					   time/ft_time.c \
					   utils/ft_atol.c \
					   utils/ft_error.c \
					   utils/ft_isnum.c
endif
SRC_C				:= $(addprefix $(SRC_DIR)/,$(SRC_C))

# OBJ
OBJ_C				:= $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRC_C:%.c=%.o))

# LIB DIR
CFLAGS				+= $(INC_DIR)

#  Bash Color / unicode char

#get_random		= $(shell seq 0 256 | shuf | head -n1)
green				:= \033[38;5;82m
blue				:= \033[38;5;75m
red					:= \033[38;5;196m
orange				:= \033[38;5;214m

blinking			:= \033[5m
reset				:= \033[0m

font_color			:= $(blue)
bold				:= $(green)
ascii_color			:= $(bold)

green_plus			:= $(font_color)[$(green)+$(font_color)]
red_minus			:= $(font_color)[$(red)-$(font_color)]
orange_star			:= $(font_color)[$(orange)*$(font_color)]
blinking_arrow		:= $(blinking)$(font_color)->
#font_color			:= \033[38;5;$(get_random)m
#bold				:= \033[38;5;$(get_random)m
#ascii_color		:= \033[38;5;$(get_random)m

UL="\xe2\x95\x94"
HO="\xe2\x95\x90"
UR="\xe2\x95\x97"
VE="\xe2\x95\x91"
LL="\xe2\x95\x9a"
LR="\xe2\x95\x9d"

# **************************************************************************** #

# **************************************************************************** #
# utils

define ascii_art
██████╗ ██╗  ██╗██╗██╗      ██████╗
██╔══██╗██║  ██║██║██║     ██╔═══██╗
██████╔╝███████║██║██║     ██║   ██║
██╔═══╝ ██╔══██║██║██║     ██║   ██║
██║     ██║  ██║██║███████╗╚██████╔╝
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝
$(reset)
endef
export ascii_art

define print_padded
	@printf '   $(orange_star) $(font_color)Creation of $(bold)$1'
	$(eval OBJ_LEN := $(shell printf $1 | wc -c))
	$(eval PAD_LEN := $(shell expr $(PADDING) - $(OBJ_LEN)))
	@printf '%-$(PAD_LEN)s' ' '
	@printf '$(blinking_arrow) $(reset)$(bold)$2 $(reset)'
	@printf '\n'
endef

define usage
$(orange_star) $(bold)$(TARGET)$(font_color): $(bold)needed_args \
$(font_color)[$(bold)optional_args$(font_color)]$(reset)
        $(bold)arg$(font_color): eplanation
        $(bold)arg$(font_color): eplanation
        $(bold)arg$(font_color): eplanation, $(bold)WARNING$(reset)
$(font_color)Version: $(bold)$(VERSION)$(reset)

endef
export usage

define make_dir
	@if [ ! -d $1 ]; then														\
		mkdir $1;																\
		printf "$(green_plus) $(font_color)Create dir $(bold)$1$(reset)\n";		\
	fi
endef

# **************************************************************************** #

# **************************************************************************** #
# Rules

all:					setup $(TARGET)
	@printf "$$usage"

bonus:					setup $(TARGET)
	@printf "$$usage"

$(TARGET):				$(OBJ_C)
	@printf "$(green_plus) $(font_color)Creation of $(bold)$@$(reset)\n"
	@$(CC) $(CFLAGS) -o $@ $(OBJ_C)

$(OBJ_DIR)/%.o: 		$(SRC_DIR)/%.c
	$(call print_padded,$^,$@)
	@$(CC) $(CFLAGS) -o $@ -c $<

setup:					call_logo $(OBJ_SUBDIR)
ifeq ($(wildcard $(BIN_DIR)),)
	@printf "$(green_plus) $(font_color)Create dir $(bold)$(BIN_DIR)$(reset)\n"
	@mkdir $(BIN_DIR)
endif

call_logo:
	@printf "$(ascii_color)$$ascii_art"

$(OBJ_SUBDIR):
	$(foreach dir,$@,$(call make_dir,$(dir)))

clean:
ifneq ($(wildcard ./obj),)
	@printf "$(red_minus) $(font_color)Deleting $(bold)obj$(reset)\n"
	@$(RM) ./obj
endif
ifneq ($(wildcard ./obj_bonus),)
	@printf "$(red_minus) $(font_color)Deleting $(bold)obj_bonus$(reset)\n"
	@$(RM) ./obj_bonus
endif

fclean:					clean
ifneq ($(wildcard ./bin/philo),)
	@printf "$(red_minus) $(font_color)Deleting $(bold)bin/philo$(reset)\n"
	@$(RM) ./bin/philo
endif
ifneq ($(wildcard ./bin/philo_bonus),)
	@printf "$(red_minus) $(font_color)Deleting $(bold)bin/philo_bonus$(reset)\n"
	@$(RM) ./bin/philo_bonus
endif
ifneq ($(wildcard $(BIN_DIR)),)
	@printf "$(red_minus) $(font_color)Deleting $(bold)$(BIN_DIR)$(reset)\n"
	@$(RM) -rf $(BIN_DIR)
endif

re:						fclean all

.PHONY:					all clean fclean re setup call_logo bonus

# **************************************************************************** #
