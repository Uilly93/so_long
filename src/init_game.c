/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:11:01 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 10:49:41 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	get_pos(t_utils *params ,t_check *check)
{
	while (params->map[params->map_y])
	{
		params->map_x = 0;
		while (params->map[params->map_y][params->map_x])
		{
			check_character(params);
			check_collectibles(params);
			check_exit(params);
			params->map_x++;
		}
		params->map_y++;
	}
	if(check_error(params))
		return (1);
	get_check_pos(params, check);
	if(flood_fill(check, check->pos_x, check->pos_y))
		return (1);
	if(check_after_filled(check->map))
		return(1);
	return (0);
}
int	load_sprites(t_utils *params)
{
	int height = TILE_SIZE;
	int width = TILE_SIZE;
	
	params->walls = mlx_xpm_file_to_image(params->mlx_ptr, \
								"textures/wall.xpm", &width, &height);
	if(!params->walls)
		return (1);
	params->floor = mlx_xpm_file_to_image(params->mlx_ptr, \
								"textures/floor.xpm", &width, &height);
	if(!params->floor)
		return (1);
	params->collectibles = mlx_xpm_file_to_image(params->mlx_ptr, \
								"textures/collectible.xpm", &width, &height);
	if(!params->collectibles)
		return (1);
	params->character = mlx_xpm_file_to_image(params->mlx_ptr, \
								"textures/p.xpm", &width, &height);
	if(!params->character)
		return (1);
	params->exit = mlx_xpm_file_to_image(params->mlx_ptr, \
								"textures/exit.xpm", &width, &height);
	if(!params->exit)
		return (1);
	return (0);
}
int	init_window_hooks(t_utils *params, t_check *check)
{
	if(get_pos(params, check))
		return (1);
	params->mlx_ptr =  mlx_init();
	if (!params->mlx_ptr)
		return(1);
	if (load_sprites(params))
	{
		write(2, "Error:\nSprites loading failed.\n", 31);
		return (1);
	}
	params->win_ptr = mlx_new_window(params->mlx_ptr, WINDOW_WIDTH,\
										WINDOW_HEIGHT, "so_long");
	if (!params->win_ptr)
		return (1);
	params->canvas = mlx_new_image(params->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_hook(params->win_ptr, DestroyNotify, 0, quit_game, params);
	mlx_loop_hook(params->mlx_ptr, ft_display_map, params);
	mlx_key_hook(params->win_ptr, get_key, params);
	mlx_loop(params->mlx_ptr);
	return (0);
}
