# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: badal-la <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 19:45:10 by badal-la          #+#    #+#              #
#    Updated: 2025/01/28 16:08:56 by badal-la         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    LIBRARY                                   #
# **************************************************************************** #

LIBFT_DIR = libft
PRINTF_DIR = ft_printf
GNL_DIR = get_next_line
INCLUDE_DIR = includes

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
GNL_SRCS = $(GNL_DIR)/get_next_line_bonus.c \
			$(GNL_DIR)/get_next_line_utils_bonus.c
			
GNL_OBJS = $(GNL_SRCS:.c=.o)

# **************************************************************************** #
#                                   MANDATORY                                  #
# **************************************************************************** #

SRC =	mandatory/main.c \
		mandatory/errors.c

OBJ = $(SRC:.c=.o)

# **************************************************************************** #
#                                     BONUS                                    #
# **************************************************************************** #

# **************************************************************************** #
#                                   VARIABLES                                  #
# **************************************************************************** #

NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -I $(PRINTF_DIR)

# **************************************************************************** #
#                                     RULES                                    #
# **************************************************************************** #

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo ✅ "Libft compiled\n"

$(PRINTF):
	@make -C $(PRINTF_DIR)
	@echo ✅ "ft_printf compiled\n"

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(GNL_OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJ) $(GNL_OBJS) \
		-L $(LIBFT_DIR) -lft \
		-L $(PRINTF_DIR) -lftprintf
	@echo ✅ "Mandatory part compiled\n"

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

# **************************************************************************** #
#                                     CLEAN                                    #
# **************************************************************************** #
clean:
	rm -f $(OBJ) $(GNL_OBJS)
	@make clean -C $(LIBFT_DIR)
	@make clean -C $(PRINTF_DIR)
#	rm -f $(OBJS_BONUS)
	@echo ✅ "Objects files removed\n"

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
#	rm -f $(NAME_BONUS)
	@echo ✅ "Executables and objects files removed\n"

re:	fclean all

##############################################################################

.PHONY: all clean fclean re
