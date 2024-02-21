# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    mallocator.mk                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/15 07:49:34 by thzeribi          #+#    #+#              #
#    Updated: 2024/02/21 12:57:02 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

malloc_test: makelib $(PATH_MLX)/libmlx.a $(OBJECTS)
		$(CC) $(CFLAGS) -g $(INCLUDES) -fsanitize=undefined -rdynamic -o $@ $(OBJECTS) $(LDFLAGS) -L. -lmallocator

.PHONY: malloc_test
