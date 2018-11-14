.PHONE: all clean fclean

CC = gcc
CFLAGS= -Wall -Wextra -Werror -g
INCLUDE= -I srcs/includes
LDFLAGS = -shared
SRC= srcs/ft_malloc.c srcs/ft_region_list.c srcs/ft_zone_list.c srcs/ft_region_tools.c srcs/ft_putstr.c srcs/ft_strlen.c \
srcs/ft_putnbr_base.c srcs/ft_show_alloc_mem.c srcs/ft_free.c srcs/ft_realloc.c srcs/ft_optimize.c
OBJECTS= $(SRC:.c=.o)

ifeq ($(HOSTTYPE),)
    HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME= libft_malloc_$(HOSTTYPE).so

all:$(NAME)

test: all
	@gcc -L $(shell pwd) $(CFLAGS) -o malloc main.c -lft_malloc

$(NAME):$(OBJECTS)
	@$(CC) $^ $(LDFLAGS) -o $@ $(INCLUDE) $(CFLAGS)
	ln -sf $(NAME) libft_malloc.so

%.o:%.c
	@$(CC) -o $@ -c $< $(INCLUDE) $(CFLAGS)

clean:
	@rm -rf $(OBJECTS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf libft_malloc.so
	@rm -rf malloc

re: fclean test