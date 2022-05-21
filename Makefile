# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/11 20:03:14 by kfumiya           #+#    #+#              #
#    Updated: 2021/06/06 06:59:58 by kfumiya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	main.c \
					test.c \
					gnl/get_next_line.c gnl/get_next_line_utils.c \
					utils/pos.c utils/ft_endwith.c utils/ft_in_set.c \
					utils/str.c utils/ft_atoi.c utils/ft_itoa.c\
					utils/ft_split.c utils/ft_strcmp.c \
					utils/ft_strdup.c utils/ft_substr.c \
					utils/ft_write.c \
					game.c errors.c clear.c \
					parse_params.c parse_textures.c parse_map.c check_map.c \
					parse_sprites.c parse_config.c \
					window.c texture.c color.c sprite.c
					# camera.c tables.c screen.c \
					# draw.c raycast.c draw_wall.c draw_ceiling_floor.c \
					# cub3d.c
					# tables.c
					
					



OBJS	= $(SRCS:.c=.o)

NAME	= cub3D

GCC		= gcc

FLAGS	= -O3 -Wall -Wextra -Werror

INCLUDES	= -I mlx

MLX_LIB = mlx/libmlx.dylib

all:	$(NAME)

.PHONY:	clean fclean re bonus bench bclean

$(NAME):	$(OBJS)
	@make -C gnl
	@make -C mlx
	cp $(MLX_LIB) libmlx.dylib
	gcc $(FLAGS) -g -o $(NAME) $(OBJS) -Lgnl -lgnl -Lmlx -lmlx -framework OpenGL -framework AppKit

clean:
	rm -f $(OBJS)
	@make -C mlx clean
	@make -C gnl clean

fclean: clean
	@make -C mlx fclean
	@make -C gnl fclean
	rm -f $(NAME)
	rm -f libmlx.dylib
	rm -f screenshot.bmp

re: fclean all

%.o: %.c
	$(GCC) $(INCLUDES) -c $<  -o $(<:.c=.o)

run: all
	@./cub3D test.cub
