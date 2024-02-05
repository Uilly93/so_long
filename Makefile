NAME = so_long
INCLUDES = libft/
CC = cc
MINILIBX = minilibx-linux/
LIBFT = libft/
SRC = src/test.c
OBJS = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

all: minilibx libft $(NAME)


$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft -L$(MINILIBX) -lmlx -lmlx_Linux -lXext -lbsd -lm -lX11
	
clean:
	$(RM) $(OBJS)
	cd $(LIBFT) && make clean
	cd $(MINILIBX) && make clean
	
fclean: clean
	$(RM) $(NAME)
	cd $(LIBFT) && make fclean
	cd $(MINILIBX) && make clean

re: fclean all

minilibx:
	$(MAKE) -C $(MINILIBX)

libft:
	$(MAKE) -C $(LIBFT)

.PHONY: all clean fclean re minilibx libft