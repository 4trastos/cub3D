NAME = cub3D

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

RM = rm -f

LIB = ar rcs

# LINKS = -I /usr/local/include -L /usr/local/lib \
#     -l mlx -l ft -framework OpenGL -framework Appkit

SRC = src/main.c \
		src/error_free.c \
		src/parse.c \
		src/map_checker.c \
		src/create_struct.c \
		src/cartridge.c \
		utils/utils.c \
		utils/utils_02.c \
		utils/ft_itoa.c \
		utils/ft_atoi.c \
		utils/ft_split.c \
		utils/get_next_line.c

OBJS = $(SRC:.c=.o)

all: $(NAME) #./minilibx-linux/Makefile

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(OBJS)

re: fclean all

.PHONY: all clean fclean re