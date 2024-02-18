/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:12 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 13:17:45 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

typedef struct s_utils
{
	int		map_row;
	int		map_col;
	int		map_x;
	int		map_y;
	int		map_width;
	int		map_height;
	int		pos_x;
	int		pos_y;
	int		door_x;
	int		door_y;
	int		collected;
	int		door_count;
	int		nb_character;
	int		step;
	int		height;
	int		width;

	char	**map;
	void	*floor;
	void	*walls;
	void	*exit;
	void	*character;
	void	*collectibles;

	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*canvas;

}	t_utils;

typedef struct s_check
{
	char	**map;
	int		map_y;
	int		map_x;
	int		pos_x;
	int		pos_y;
	int		max_x;
	int		max_y;
	int		collected;
	int		door_count;
	int		nb_character;

}	t_check;

# define TILE_SIZE 64

int		init_window_hooks(t_utils *params, t_check *check); //init_game.c
int		load_sprites(t_utils *params);
int		get_pos(t_utils *params, t_check *check);

int		parsing_line_count(t_utils *params, char *path); //parsing_map.c
int		parsing_map(t_utils *params, char *path);
void	identify_sprites(t_utils *params, int x, int y);
void	ft_draw_sprite(t_utils *params, t_img *img, int x, int y);

void	put_wall(t_utils *params, int x, int y); // draw_sprites.c
void	put_floor(t_utils *params, int x, int y);
void	put_collectibles(t_utils *params, int x, int y);
void	put_character(t_utils *params, int x, int y);
void	put_exit(t_utils *params, int x, int y);

int		display_sprites(t_utils *params); //display_sprites.c
int		ft_display_map(t_utils *params);
void	display_character(t_utils *params);
void	display_door(t_utils *params);
int		switch_sprite(t_utils *params, int nb);

void	update_collectibles(t_utils *params); //loop_update.c
void	update_pos(t_utils *params);
int		move_character(int key, t_utils *params);
int		get_key(int key, t_utils *params);

int		quit_game(t_utils *params); //close_game.c
void	close_window(t_utils *params);
void	ft_free_map(char **map);
void	destroy_images_map(t_utils *params, t_check *check);

int		check_error(t_utils *params); //check_errors.c
void	check_exit(t_utils *params);
void	check_character(t_utils *params);
void	check_collectibles(t_utils *params);

int		check_input(char c); //check_errors_utils.c
int		check_map(t_utils *params);
int		check_walls(t_utils *params);
int		check_map_edges(t_utils *params);
int		check_line(t_utils *params);

void	get_check_pos(t_utils *params, t_check *check); //parsing_errors.c
int		flood_fill(t_check *map, int x, int y);
int		check_after_filled(char **map);

#endif