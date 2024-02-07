/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:12 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/07 17:26:34 by wnocchi          ###   ########.fr       */
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
	int		fd;
	int		map_row;
	int		map_col;
	int		key_bind;
	int		map_x;
	int		map_y;
	int		map_width;
	int		map_height;
	
	char 	**map;
	char	*path_sprites;
	void	*sprites;
	int		*sprite_width;
	int		*sprite_height;
	void	*floor;
	void	*walls;
	void	*exit;
	void	*character;
	void	*collectibles;
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	*canvas;
	
}	t_utils;

# define TILE_SIZE 64

#endif