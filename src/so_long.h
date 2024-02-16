/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:12 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/16 11:08:36 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx_int.h"
# include "../minilibx-linux/mlx.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720

typedef	struct s_utils
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

	char 	**map;
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

#endif

// 11111111111111111111
// 1000P00000000C100001
// 1110000C00000010C001
// 10000010000000100001
// 11100000000001110001
// 10000000000001100001
// 10001010000100100001
// 10000010000000100001
// 1000000C0000C0000001
// 100000000000110000E1
// 11111111111111111111