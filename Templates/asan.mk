# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    asan.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 03:01:58 by thzeribi          #+#    #+#              #
#    Updated: 2024/02/22 07:59:06 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
asan:
	$(MAKE) DBG=1 header makelib $(NAME)

.DBG.$(DEBUG): 
	rm -f .DBG.*
	touch $@

.PHONY: asan
