# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    header.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 01:52:22 by thzeribi          #+#    #+#              #
#    Updated: 2026/05/12 14:50:28 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


AUTHOR	:= thzeribi
DATE	:= $(shell date +%F)

define print_header
	printf "%b" "$(INFO_COLOR)";
	echo "=============================================================================================="
	printf "\033[m$(INFO_COLOR)$(OK_COLOR)Name:	$(OBJ_COLOR)%s %b\033[m" "$(PROJECT_NAME)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)Author: $(OBJ_COLOR)%s %b\033[m" "$(AUTHOR)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)Date: $(OBJ_COLOR)%s %b\033[m" "$(DATE)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)CC: $(OBJ_COLOR)%s %b\033[m" "$(CC)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)Flags: $(OBJ_COLOR)%s %b\033[m" "$(CFLAGS)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)LDFlags: $(OBJ_COLOR)%s %b\033[m" "$(LDFLAGS)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)LBLibs: $(OBJ_COLOR)%s %b\033[m" "$(LDLIBS)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)DEBUG: $(OBJ_COLOR)%s %b\033[m" "$(DBG)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)BONUS: $(OBJ_COLOR)%s %b\033[m" "$(BNS)" "$(INFO_COLOR)\n"
	printf "$(INFO_COLOR)$(OK_COLOR)MAKECMDGOALS:$(OBJ_COLOR) %s %b\033[m" "$(MAKECMDGOALS)" "$(INFO_COLOR)\n"; \
	printf "$(INFO_COLOR)==============================================================================================\n"
endef

header:
ifdef TERM
	clear
endif
	$(call print_header)
