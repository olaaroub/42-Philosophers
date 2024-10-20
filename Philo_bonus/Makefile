# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olaaroub <olaaroub@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/08 20:43:53 by olaaroub          #+#    #+#              #
#    Updated: 2024/10/20 16:54:04 by olaaroub         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -fsanitize=thread -g3

SRC = src/main_bonus.c src/utils/utils-v1_bonus.c src/check_args_bonus.c src/initialization_bonus.c
SRC += src/prep_start_simulation_bonus.c src/utils/read_write_bonus.c src/utils/utils-v2_bonus.c
SRC += src/admin_routine_bonus.c src/utils/ft_strjoin.c src/utils/ft_itoa.c src/utils/ft_strdup.c

OBJ = $(SRC:.c=.o)

NAME = philo_bonus

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
