NAME = cub3D

CC = gcc

CFLAGS = -Wall -Werror -Wextra #-g3 -fsanitize=address

RM = rm -f

LIB = ar rcs

EXTRA = -I ./incl -I $(LIBMLX)/include

LIBMLX = ./MLX42-master

MLX42 = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC = src/main.c \
		src/error_free.c \
		src/parse.c \
		src/map_checker.c \
		src/create_struct.c \
		src/cartridge.c \
		src/cartridge_2.c \
		src/raycast.c \
		src/brain.c \
		bits/binary_encoding.c \
		utils/utils.c \
		utils/utils_02.c \
		utils/ft_itoa.c \
		utils/ft_atoi.c \
		utils/ft_split.c \
		utils/get_next_line.c

OBJS = $(SRC:.c=.o)

all: libmlx $(NAME) 

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLX42) $(EXTRA) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re