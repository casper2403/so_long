# var voor compilerkeuze
CC = cc

# compiler flags
CFLAGS = -Wall -Werror -Wextra -I. -g

# c files var
CFILES = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c

# de files in ft_printf
CFILES += ft_printf/ft_printf.c ft_printf/print_c.c ft_printf/print_d.c ft_printf/print_i.c ft_printf/print_p.c ft_printf/print_percent.c ft_printf/print_s.c ft_printf/print_u.c ft_printf/print_upperx.c ft_printf/print_x.c

# naam van lib
NAME = libft.a

# convert c files naar o files
OFILES = $(CFILES:.c=.o)

# default option
# checkt of NAME bestaat en voort deze dan uit, zie line 17
# cleant daarna de o files
all : $(NAME)

# compiled de library
# checkt of er OFILES bestaan en runt dan de command voor de library
$(NAME) : $(OFILES)
	ar rcs $(NAME) $(OFILES)

# verwijdert de OFILES
clean:
	rm -f $(OFILES)

# verwijdert de OFILES en de libft.a
fclean : clean
	rm -f $(NAME)

# verwijdert alles en rebuilt
re: fclean all
