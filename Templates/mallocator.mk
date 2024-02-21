# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mallocator.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 07:49:34 by thzeribi          #+#    #+#              #
#    Updated: 2023/01/17 11:09:52 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

malloc_test: makelib $(PATH_MLX)/libmlx.a $(OBJECTS)
		$(CC) $(CFLAGS) -g $(INCLUDES) -fsanitize=undefined -rdynamic -o $@ ${OBJECTS} $(LIBFT) $(MLX) -L. -lmallocator

.PHONY: malloc_test