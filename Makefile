# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: student <student@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/23 19:45:10 by badal-la          #+#    #+#              #
#    Updated: 2025/02/07 16:03:27 by student          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                    LIBRARY                                   #
# **************************************************************************** #

LIBFT_DIR = libft
PRINTF_DIR = ft_printf
GNL_DIR = get_next_line
MLX_LINUX_DIR = minilibx-linux
MLX_MAC_DIR = minilibx_macos
INCLUDE_DIR = includes

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
GNL_SRCS = $(GNL_DIR)/get_next_line_bonus.c \
			$(GNL_DIR)/get_next_line_utils_bonus.c
			
GNL_OBJS = $(GNL_SRCS:.c=.o)

# **************************************************************************** #
#                         DETECTION DE L'OS & FLAGS                            #
# **************************************************************************** #

UNAME := $(shell uname)

#ifeq ($(UNAME), Linux)
MLX_DIR = $(MLX_LINUX_DIR)
MLX = $(MLX_LINUX_DIR)/libmlx.a
MLX_FLAGS = -L $(MLX_DIR) -lmlx -lX11 -lXext -lm
#else
#	MLX_DIR = $(MLX_MAC_DIR)
#	MLX = $(MLX_MAC_DIR)/libmlx.a
#	MLX_FLAGS = -L $(MLX_DIR) -lmlx -framework OpenGL -framework AppKit -I /opt/X11/include -L /opt/X11/lib
#endif

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
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I $(INCLUDE_DIR) -I $(LIBFT_DIR) -I $(PRINTF_DIR) -I $(MLX_DIR)

# **************************************************************************** #
#                                     RULES                                    #
# **************************************************************************** #

all: $(NAME)

$(MLX):
	@make -C $(MLX_DIR)
	@echo ✅ "Minilibx compiled\n"

$(LIBFT):
	@make -C $(LIBFT_DIR)
	@echo ✅ "Libft compiled\n"

$(PRINTF):
	@make -C $(PRINTF_DIR)
	@echo ✅ "ft_printf compiled\n"

$(NAME): $(OBJ) $(LIBFT) $(PRINTF) $(GNL_OBJS) $(MLX)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJ) $(GNL_OBJS) \
		-L $(LIBFT_DIR) -lft \
		-L $(PRINTF_DIR) -lftprintf \
		$(MLX_FLAGS)
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
	@make clean -C $(MLX_DIR) || true
#	rm -f $(OBJS_BONUS)
	@echo ✅ "Objects files removed\n"

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)
	@make fclean -C $(PRINTF_DIR)
#	@make fclean -C $(MLX_DIR)
#	rm -f $(NAME_BONUS)
	@echo ✅ "Executables and objects files removed\n"

re:	fclean all

test: $(NAME)
	./$(NAME) test_maps/t2.fdf

vtest: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 42.fdf
##############################################################################

.PHONY: all clean fclean re test
