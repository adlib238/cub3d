NAME			= cub3D
CC				= cc
INCLUDES		= -I./includes
CFLAGS			= -Wall -Werror -Wextra -MMD -MP $(INCLUDES)

SRC_DIR			= srcs/
SRC_FILE		:= main.c validation.c init.c \
					parse_cubfile.c parse_colors.c parse_textures.c parse_map.c \
					utils.c get_next_line.c free.c exit.c \
					draw_wall.c	error.c game.c init_player.c mlx_utils.c \
					vector.c wall_utils.c player.c hooks.c math_utils.c
SRC				= $(addprefix $(SRC_DIR), $(SRC_FILE))

OBJ_DIR			= obj/
OBJ				= $(addprefix $(OBJ_DIR), $(SRC_FILE:%.c=%.o))
DEPEND			= $(OBJ:%.o=%.d)

LIBFT_DIR		= libft/
LIBFT_NAME		= libft.a

UNAME			= $(shell uname)
ifeq ($(UNAME), Darwin)
	MLXFLAG = -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
else
	ifeq ($(UNAME), Linux)
		MLXFLAG = -Imlx -lXext -lX11 -lm
	endif
endif
MLX_DIR		= mlx/
MLX_NAME	= libmlx_$(UNAME).a

LIBFT			= $(LIBFT_DIR)$(LIBFT_NAME)
LIBMLX			= $(MLX_DIR)$(MLX_NAME)
LIBS			= $(LIBFT) $(LIBMLX)

all: $(NAME)

$(NAME): $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(MLXFLAG)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	make -C $(MLX_DIR)
	make -C $(LIBFT_DIR)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)
	@if [ -d $(OBJ_DIR) ]; then rm -r $(OBJ_DIR) ; fi

fclean: clean
	make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

bonus: all

-include $(DEPEND)
.PHONY: all clean fclean re bonus
