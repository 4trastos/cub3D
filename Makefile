NAME = cub3D

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I/usr/include -Imlx_linux -g3 -fsanitize=address

RM = rm -f

LIB = ar rcs

LIBMLX = ./MLX

MLX	= -I ./include -I $(LIBMLX)/include

LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC = src/main.c \
		src/error_free.c \
		src/parse.c \
		src/map_checker.c \
		src/create_struct.c \
		src/cartridge.c \
		src/cartridge_2.c \
		src/brain.c \
		src/brain_2.c \
		src/brain_3.c \
		src/raycast.c \
		bits/binary_encoding.c \
		utils/utils.c \
		utils/utils_02.c \
		utils/utils_03.c \
		utils/ft_itoa.c \
		utils/ft_atoi.c \
		utils/ft_split.c \
		utils/get_next_line.c \
		utils/raycast_utils.c

OBJS = $(SRC:.c=.o)

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX) $(LIBS) $(CFLAGS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re