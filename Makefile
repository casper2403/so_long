NAME_EXEC	= so_long
LIBFT		= lib/libft/libft.a
MLX		= lib/mlx_linux/libmlx_Linux.a
CC		= cc
CFLAGS		= -Wall -Wextra -g -Llib/mlx_linux -lmlx_Linux \
		  -Ilib/mlx_linux -lXext -lX11
OFLAGS		= -Wall -Wextra -g
OBJ		= obj

# Source files
EXEC_SRCS	= src/main.c src/floodfill.c src/movement.c src/map_check.c src/cleanup.c src/init.c src/map_check2.c

# Object files in the obj folder
EXEC_OBJS	= $(EXEC_SRCS:src/%.c=obj/%.o)

all:		$(LIBFT) $(MLX) $(NAME_EXEC)

$(NAME_EXEC):	$(EXEC_OBJS)
		$(CC) $(EXEC_OBJS) $(CFLAGS) $(LIBFT) -o $(NAME_EXEC)

obj/%.o: src/%.c | $(OBJ)
		$(CC) $(OFLAGS) -c $< -o $@

$(OBJ):
		mkdir -p $(OBJ)

$(MLX):
		make -C lib/mlx_linux

$(LIBFT):
		make -C lib/libft

clean:
		rm -rf $(OBJ)
		make -C lib/libft clean
		make -C lib/mlx_linux clean

fclean:		clean
		rm -f $(NAME_EXEC)
		make -C lib/libft fclean

re:		fclean all

.PHONY:		all clean fclean re
