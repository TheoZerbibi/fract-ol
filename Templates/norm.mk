# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    norme.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/26 00:45:47 by thzeribi          #+#    #+#              #
#    Updated: 2023/01/15 10:23:29 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

norm: header
ifneq ($(LIBFT_FOLDER),)
	$(MAKE) -C $(LIBFT_FOLDER) norm
endif
	printf "\n$(INFO_COLOR)$(PROJECT_NAME) $(NO_COLOR)Norm check$(NO_COLOR).\n\n"
	norminette ${SOURCES_FOLDER} ${INCLUDES_FOLDER} $(LIBFT_FOLDER) | grep 'Error' ; true
.PHONY: norm