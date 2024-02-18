NAME = so_long
INCLUDES = libft/
CC = cc
MINILIBX = minilibx-linux/
LIBFT = libft/
SRC_DIR = src
OBJ_DIR = obj
SRC_NAME = main.c draw_sprites.c init_game.c parsing_map.c \
	display_sprites.c loop_update.c close_game.c \
	check_errors.c check_errors_utils.c parsing_errors.c
OBJS = $(addprefix $(OBJ_DIR)/,$(SRC_NAME:%.c=%.o))
SRC = $(addprefix $(SRC_DIR)/,$(SRC_NAME))
SPRITES = textures/floor.xpm textures/wall.xpm \
	textures/collectible.xpm textures/p.xpm textures/rp.xpm \
	textures/exit.xpm textures/open.xpm
CFLAGS = -Wall -Wextra -Werror -g3 -O2 -fno-builtin
RM = rm -rf

all: minilibx libft $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(SPRITES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft -L$(MINILIBX) -lmlx -lmlx_Linux -lXext -lbsd -lm -lX11  
	
clean:
	$(RM) $(OBJ_DIR)
	cd $(LIBFT) && make clean
	cd $(MINILIBX) && make clean
	
fclean: clean
	$(RM) $(NAME)
	cd $(LIBFT) && make fclean
	cd $(MINILIBX) && make clean

re: fclean all

exe: all
	./so_long map/map.ber

valgrind: all
	valgrind ./so_long map/map.ber

minilibx:
	$(MAKE) -C $(MINILIBX)

libft:
	$(MAKE) -C $(LIBFT)

.PHONY: all clean fclean re minilibx libft