# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkuokka <vkuokka@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/10 12:10:34 by vkuokka           #+#    #+#              #
#    Updated: 2020/02/28 15:03:31 by vkuokka          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = srcs/main.c \
       srcs/config_terminal.c \
       srcs/config_signal.c \
       srcs/utils.c \
       srcs/input/user_input.c \
       srcs/input/special_keys.c \
       srcs/input/arrow_navigation.c \
       srcs/input/history_navigation.c \

INCL =	includes/
INCL1 = libftprintf/includes
INCL2 = libftprintf/libft/includes

LIB = ftprintf
LIBFOL = libftprintf/

all: $(NAME)
$(NAME):
	#make -C libftprintf/
	gcc -Wall -Werror -Wextra -I $(INCL) -I $(INCL1) -I $(INCL2) $(SRCS) -L$(LIBFOL) -l$(LIB) -ltermcap -o $(NAME)
clean:
	#make -C libftprintf/ clean

fclean: clean
	#make -C libftprintf/ fclean
	rm -f $(NAME)

re: fclean all
