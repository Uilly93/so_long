/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:12 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/06 16:41:13 by wnocchi          ###   ########.fr       */
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
	int		map_width;
	int		map_height;
	int		key_bind;
	
	char 	**map;
	char	*path_sprites;
	void	*sprites;
	int		*sprite_width;
	int		*sprite_height;
	void	*background;
	void	*walls;
	void	*exit;
	void	*character;
	void	*collectibles;
	void	*mlx_ptr;
	void	*win_ptr;
	
}	t_utils;

#endif