# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 20:43:53 by olaaroub          #+#    #+#              #
#    Updated: 2024/10/21 09:31:25 by olaaroub         ###   ########.fr        #
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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(NAME_BONUS)

clean:
	@rm -rf $(OBJ) $(OBJ_BONUS)

fclean: clean
	@rm -rf $(NAME) $(NAME_BONUS)

re: fclean all

.PHONY: clean fclean re all bonus
.SECONDARY: $(OBJ) $(OBJ_BONUS)
