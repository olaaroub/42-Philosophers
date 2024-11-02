# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 20:43:53 by olaaroub          #+#    #+#              #
#    Updated: 2024/11/02 21:37:26 by olaaroub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = cc
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=thread -g3

SRC = src/main_bonus.c src/utils/utils-v1_bonus.c src/check_args_bonus.c src/initialization_bonus.c
SRC += src/prep_start_simulation_bonus.c src/utils/read_write_bonus.c
SRC += src/admin_routine_bonus.c src/utils/ft_strjoin.c src/utils/ft_itoa.c
SRC += src/utils/utils-v3.c src/utils/ft_strdup.c src/utils/utils-v2_bonus.c

OBJ = $(SRC:.c=.o)

NAME = philo_bonus

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
