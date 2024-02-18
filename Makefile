NAME = so_long
INCLUDES = libft/
CC = cc
MINILIBX = minilibx-linux/
LIBFT = libft/
SRC = src/main.c src/draw_sprites.c src/init_game.c src/parsing_map.c \
	src/display_sprites.c src/loop_update.c src/close_game.c \
	src/check_errors.c src/check_errors_utils.c src/parsing_errors.c
OBJS = $(SRC:.c=.o)
SPRITES = textures/floor.xpm textures/wall.xpm \
	textures/collectible.xpm textures/p.xpm textures/rp.xpm \
	textures/exit.xpm textures/open.xpm
CFLAGS = -Wall -Wextra -Werror -g3 -O2 -fno-builtin
RM = rm -f

all: minilibx libft $(NAME)

$(NAME): $(OBJS) $(SPRITES)
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

exe: re
	./so_long map/map.ber

valgrind: re
	valgrind ./so_long map/map.ber

minilibx:
	$(MAKE) -C $(MINILIBX)

libft:
	$(MAKE) -C $(LIBFT)

.PHONY: all clean fclean re minilibx libft