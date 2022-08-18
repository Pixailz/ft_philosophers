# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/23 01:36:34 by brda-sil          #+#    #+#              #
#    Updated: 2022/08/18 22:14:53 by brda-sil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
# config
CFLAGS			:= -Wall -Wextra -I. -pthread
TARGET			:= philo_bonus
RM				:= rm -rf
CC				:= gcc
MAKE			:= make -C
VERSION			:= 3.1.5
$(eval export MAIN=1)

ifeq ($(DEBUG),1)
CFLAGS			+= -g3
endif
ifeq ($(DEBUG_THREAD),1)
CFLAGS			+= -fsanitize=thread
endif

ifneq ($(DEBUG),1)
ifneq ($(DEBUG_THREAD), 1)
CFLAGS			+= -Werror
endif
endif

ifneq ($(PADDING),40)
PADDING			:= 40
endif

# SRC
SRC_C				:= dataset/free_bonus.c \
					   dataset/init_bonus.c \
					   dataset/parse_bonus.c \
					   debug/debug_bonus.c \
					   philosophers_bonus.c \
					   utils/ft_atol_bonus.c \
					   utils/ft_error_bonus.c \
					   utils/ft_get_timestamp_ms_bonus.c \
					   utils/ft_isnum_bonus.c \
					   utils/ft_strlen_bonus.c \
					   world/eat_bonus.c \
					   world/god_bonus.c \
					   world/life_manager_bonus.c \
					   world/say_bonus.c \
					   world/sleep_ng_bonus.c \
					   world/solitary_life_manager_bonus.c \
					   world/utils.c

# OBJ
OBJ_C			:= $(SRC_C:%.c=%.o)

#  Bash Color / unicode char

#get_random		= $(shell seq 0 256 | shuf | head -n1)
green			:= \033[38;5;82m
blue			:= \033[38;5;75m
red				:= \033[38;5;196m
orange			:= \033[38;5;214m

blinking		:= \033[5m
reset			:= \033[0m

font_color		:= $(blue)
bold			:= $(green)
ascii_color		:= $(bold)

green_plus		:= $(font_color)[$(green)+$(font_color)]
red_minus		:= $(font_color)[$(red)-$(font_color)]
orange_star		:= $(font_color)[$(orange)*$(font_color)]
blinking_arrow	:= $(blinking)$(font_color)->
#font_color		:= \033[38;5;$(get_random)m
#bold			:= \033[38;5;$(get_random)m
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
██████╗ ██╗  ██╗██╗██╗      ██████╗ ███████╗ ██████╗ ██████╗ ██╗  ██╗███████╗██████╗ ███████╗
██╔══██╗██║  ██║██║██║     ██╔═══██╗██╔════╝██╔═══██╗██╔══██╗██║  ██║██╔════╝██╔══██╗██╔════╝
██████╔╝███████║██║██║     ██║   ██║███████╗██║   ██║██████╔╝███████║█████╗  ██████╔╝███████╗
██╔═══╝ ██╔══██║██║██║     ██║   ██║╚════██║██║   ██║██╔═══╝ ██╔══██║██╔══╝  ██╔══██╗╚════██║
██║     ██║  ██║██║███████╗╚██████╔╝███████║╚██████╔╝██║     ██║  ██║███████╗██║  ██║███████║
╚═╝     ╚═╝  ╚═╝╚═╝╚══════╝ ╚═════╝ ╚══════╝ ╚═════╝ ╚═╝     ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚══════╝
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

# **************************************************************************** #

# **************************************************************************** #
# Rules

all:			setup $(TARGET)
	@printf "$$usage"

%.o: 		%.c
	$(call print_padded,$^,$@)
	@$(CC) $(CFLAGS) -o $@ -c $<

$(TARGET):				$(OBJ_C)
	@printf "$(green_plus) $(font_color)Creation of $(bold)$@$(reset)\n"
	@$(CC) $(CFLAGS) -o $@ $(OBJ_C) $(LIBS)

setup:					call_logo

call_logo:
	@printf "$(ascii_color)$$ascii_art"

clean:
	@printf "$(red_minus) $(font_color)Deleting $(bold)obj$(reset)\n"
	@$(RM) **/*.o
	@$(RM) *.o

fclean:					clean
	@printf "$(red_minus) $(font_color)Deleting $(bold)$(TARGET)$(reset)\n"
	@$(RM) $(TARGET)

re:						fclean all

.PHONY:					all clean fclean re setup call_logo

# **************************************************************************** #
