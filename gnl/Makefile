# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kfumiya <kfumiya@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/12 12:19:43 by kfumiya           #+#    #+#              #
#    Updated: 2021/04/12 13:25:09 by kfumiya          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libgnl.a

SRC = get_next_line.c get_next_line_utils.c

OBJ = $(SRC:.c=.o)

FLAG = -Wall -Werror -Wextra

OPTION = -c

INCLUDEH	= -I ../libft


all: $(NAME)

.c.o:
	gcc $(FLAG) $(INCLUDEH) -c $< -o $@

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	rm -f $(OBJ) $(OBJBONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
