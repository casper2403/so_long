NAME_EXEC = so_long
LIBFT = libft/libft.a
CC = cc
CFLAGS = -Wall -Wextra -g -O2 -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11
OFLAGS = -Wall -Wextra -g -O2

# Source files
EXEC_SRCS = main.c

# Object files
EXEC_OBJS = $(EXEC_SRCS:.c=.o)

# Libraries
all: $(LIBFT) $(NAME_EXEC)

$(NAME_EXEC): $(EXEC_OBJS)
	$(CC) $(EXEC_OBJS) $(CFLAGS) $(LIBFT) -o $(NAME_EXEC)

%.o: %.c
	$(CC) $(OFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	rm -f $(EXEC_OBJS)
	make -C libft clean

fclean: clean
	rm -f $(NAME_EXEC)	
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
