# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norm.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 00:45:47 by thzeribi          #+#    #+#              #
#    Updated: 2026/05/12 14:24:23 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

norm: header
ifneq ($(LIBFT_FOLDER),)
	$(MAKE) -C $(LIBFT_FOLDER) norm
endif
	printf "\n$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)Norm check$(NO_COLOR).\n\n"
	norminette ${SOURCES_FOLDER} ${INCLUDES_FOLDER} | grep 'Error' ; true
.PHONY: norm
