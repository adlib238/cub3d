# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/11 20:03:14 by kfumiya           #+#    #+#              #
#    Updated: 2022/05/27 11:06:06 by kfumiya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= cub3D

SRCDIR	:= ./src
OBJDIR	:= ./obj

SRCS	:=	$(SRCDIR)/main.c \
			$(SRCDIR)/errors.c \
			$(SRCDIR)/game.c \
			$(SRCDIR)/read_cub.c \
			$(SRCDIR)/set_resolution.c \
			$(SRCDIR)/set_color.c \
			$(SRCDIR)/read_texture.c \
			$(SRCDIR)/read_map.c \
			$(SRCDIR)/set_free.c \
			$(SRCDIR)/utils.c \
			$(SRCDIR)/readline.c \
			$(SRCDIR)/check_map.c \
			$(SRCDIR)/draw_wall.c \
			$(SRCDIR)/debug.c \
			$(SRCDIR)/player.c \
			$(SRCDIR)/vector.c \
			$(SRCDIR)/wall_utils.c \
			$(SRCDIR)/set_free.c \
			$(SRCDIR)/draw.c \
			$(SRCDIR)/init_player.c \
			# $(SRCDIR)/hooks.c \
			# $(SRCDIR)/mlx_utils.c \
					# test.c \
					# gnl/get_next_line.c gnl/get_next_line_utils.c \
					# utils/pos.c utils/ft_endwith.c utils/ft_in_set.c \
					# utils/str.c utils/ft_atoi.c utils/ft_itoa.c\
					# utils/ft_split.c utils/ft_strcmp.c \
					# utils/ft_strdup.c utils/ft_substr.c \
					# utils/ft_write.c \
					# game.c errors.c clear.c \
					# parse_params.c parse_textures.c parse_map.c check_map.c \
					# parse_sprites.c parse_config.c \
					# window.c texture.c color.c sprite.c
					# camera.c tables.c screen.c \
					# draw.c raycast.c draw_wall.c draw_ceiling_floor.c \
					# cub3d.c
					# tables.c
SRCS	+=	$(SRCDIR)/debug.c \

OBJS		:= $(addprefix $(OBJDIR)/, $(notdir $(SRCS:%.c=%.o)))

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
# INCLUDES	:= -I mlx libft
INCLUDES	:= -I mlx_linux libft

LIBFT		:= libft/libft.a
MLX_LIB		:= mlx_linux/libmlx.a
# MLX_LIB		:= mlx/libmlx.dylib

RM			:= rm -rf

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@if [ ! -d $(OBJDIR) ]; then echo "mkdir -p $(OBJDIR)" && mkdir -p $(OBJDIR); fi
	$(CC) $(CFLAGS) -o $@ -c $< -Iincludes

$(NAME): $(OBJS)
	@make -C libft
	# @make -C mlx
	# @make -C mlx_linux
	# cp $(MLX_LIB) libmlx.dylib
	# cp $(MLX_LIB) libmlx.a
	# $(CC) $(CFLAGS) -g $^ -o $@ -Llib -llib -Lmlx -lmlx -framework OpenGL -framework AppKit
	$(CC) $(CFLAGS) -g $^ -o $@ $(LIBFT)
	# $(CC) $(CFLAGS) -g $^ -o $@ $(LIBFT) $(MLX_LIB)

all: $(NAME)

clean:
	$(RM) $(OBJDIR)
	@make -C libft clean
	# @make -C mlx_linux clean
	# @make -C mlx clean

fclean: clean
	@make -C libft fclean
	$(RM) $(NAME)
	# $(RM) libmlx.a
	# $(RM) libmlx.dylib
	# $(RM) screenshot.bmp

re: fclean all

run: all
	@./cub3D test.cub

.PHONY:	all clean fclean re run
