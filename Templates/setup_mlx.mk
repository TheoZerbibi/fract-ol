# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    setup_mlx.mk                                       :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thzeribi <thzeribi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 18:59:03 by thzeribi          #+#    #+#              #
#    Updated: 2025/01/04 19:23:04 by thzeribi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

setup_mlx:
	@if [ ! -d "$(MLX_FOLDER)" ]; then \
		echo "MLX_FOLDER not found. Setting up MLX..."; \
		git clone https://github.com/42Paris/minilibx-linux.git $(MLX_FOLDER); \
		$(MAKE) -C $(MLX_FOLDER); \
	else \
		echo "MLX_FOLDER already exists. Skipping setup."; \
	fi

.PHONY: setup_mlx
