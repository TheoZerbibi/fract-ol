/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjacquet <mjacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:57:39 by mjacquet          #+#    #+#             */
/*   Updated: 2023/02/28 04:17:50 by mjacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

# include <X11/keysym.h>

enum e_error {
	WALLS_ERROR,
	INVALID_CHAR,
	WRONG_NB_ARG,
	FD_ERROR,
	GNL_ERROR,
	FAIL_MALLOC,
	WRONG_EXT,
	LACK_INFOS,
	MLX_FAIL,
	TEXTURE_ERROR,
};

# define BLACK		"\e[30m"
# define RED		"\e[31m"
# define GREEN		"\e[32m"
# define YELLOW		"\e[33m"
# define BLUE		"\e[34m"
# define MAGENTA	"\e[35m"
# define CYAN		"\e[36m"
# define WHITE		"\e[37m"
# define RESET		"\e[0m"

# define TRUE 1
# define FALSE 0

# define MM_SIZE 5
# define CUB_SIZE 32

# define EXT "cub"

# define PI 3.14159265358979323846264338327950288419716939937510582
# define P2 1.57079632679
# define P3 4.71238898038 
# define DR 0.0174533

# define PLAYER_SIZE 3

# define RGB_LIGHT_GREY 0x00888888
# define RGB_RED 0x00FF0000
# define RGB_RED2 0x00FF55555
# define RGB_GREEN 0x0000FF00
# define RGB_GREEN2 0x0066AA22
# define RGB_BLUE 0x000000FF
# define RGB_WHITE 0x00FFFFFF
# define RGB_YELLOW 0x00FFFF00
# define RGB_BLACK 0x00000000
# define RGB_BROWN5 0x0042302A
# define RGB_BROWN4 0x00341107
# define RGB_BROWN3 0x00612711
# define RGB_BROWN2 0x00D18A5B
# define RGB_BROWN 0x00885500
# define RGB_SKY_BLUE 0x0065BCEB
# define RGB_TR	0xFF

#endif