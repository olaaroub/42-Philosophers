# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 20:43:53 by olaaroub          #+#    #+#              #
#    Updated: 2024/11/02 21:37:02 by olaaroub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=thread -g3

SRC = src/main.c src/utils/utils-v1.c src/check_args.c src/initialization.c
SRC += src/prep_start_simulation.c src/utils/read_write.c src/utils/utils-v2.c
SRC += src/admin_routine.c

OBJ = $(SRC:.c=.o)

NAME = philo

all:  $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ)  -o $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: clean fclean re all
.SECONDARY: $(OBJ)
