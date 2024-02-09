NAME = so_long
INCLUDES = libft/
CC = cc
MINILIBX = minilibx-linux/
LIBFT = libft/
SRC = src/test.c
OBJS = $(SRC:.c=.o)
SPRITES = src/textures/floor.png src/textures/wall.png src/textures/collectible.png src/textures/p.png src/textures/rp.png src/textures/exit.png src/textures/open.png
XPM = $(SPRITES:.png=.xpm)
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

all: minilibx libft $(NAME)

$(NAME): $(OBJS) $(XPM)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT) -lft -L$(MINILIBX) -lmlx -lmlx_Linux -lXext -lbsd -lm -lX11  

# for file in *.png; do convert $file ${file%.png}.xpm; done
%.xpm : %.png
	convert -scale 64x64 $< $@
	
clean:
	$(RM) $(OBJS) $(XPM)
	cd $(LIBFT) && make clean
	cd $(MINILIBX) && make clean
	
fclean: clean
	$(RM) $(NAME) $(XPM)
	cd $(LIBFT) && make fclean
	cd $(MINILIBX) && make clean

re: fclean all

minilibx:
	$(MAKE) -C $(MINILIBX)

libft:
	$(MAKE) -C $(LIBFT)

.PHONY: all clean fclean re minilibx libft