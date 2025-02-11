NAME_EXEC = so_long
LIBFT = lib/libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -g -O2 -Llib/mlx_linux -lmlx_Linux -Ilib/mlx_linux -lXext -lX11
OFLAGS = -Wall -Wextra -g -O2

# Source files
EXEC_SRCS = src/main.c

# Object files
EXEC_OBJS = $(EXEC_SRCS:.c=.o)

# Libraries
all: $(LIBFT) $(NAME_EXEC)

$(NAME_EXEC): $(EXEC_OBJS)
	$(CC) $(EXEC_OBJS) $(CFLAGS) $(LIBFT) -o $(NAME_EXEC)

%.o: %.c
	$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT):
	make -C lib/libft

clean:
	rm -f $(EXEC_OBJS)
	make -C lib/libft clean

fclean: clean
	rm -f $(NAME_EXEC)	
	make -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re
