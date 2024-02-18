/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:17:20 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 10:50:57 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	display_sprites(t_utils *params)
{
	int x = 0;
	int y = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			identify_sprites(params, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
int	ft_display_map(t_utils *params)
{
	display_sprites(params);
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, \
												params->canvas, 0, 0);
	return (0);
}
void	display_character(t_utils *params)
{
	put_floor(params, params->pos_x, params->pos_y);
	if (params->pos_x == params->door_x && params->pos_y == params->door_y)
		put_exit(params, params->door_x, params->door_y);
	put_character(params, params->pos_x, params->pos_y);
}

void	display_door(t_utils *params)
{
	int w;
	int h;

	w = TILE_SIZE;
	h = TILE_SIZE;
	put_floor(params, params->door_x, params->door_y);
	if (params->collected == 0)
	{
		mlx_destroy_image(params->mlx_ptr, params->exit);
		params->exit = mlx_xpm_file_to_image(params->mlx_ptr, \
		"textures/open.xpm", &w, &h);
	}
	put_exit(params, params->door_x, params->door_y);
}
int	switch_sprite(t_utils *params, int nb)
{
	int h;
	int w;

	h = TILE_SIZE;
	w = TILE_SIZE;
	if (nb == 1)
	{
		mlx_destroy_image(params->mlx_ptr, params->character);
		params->character = mlx_xpm_file_to_image(params->mlx_ptr, \
												"textures/p.xpm", &w, &h);
	}
	if (nb == 0)
	{
		mlx_destroy_image(params->mlx_ptr, params->character);
		params->character = mlx_xpm_file_to_image(params->mlx_ptr, \
												"textures/rp.xpm", &w, &h);
	}
	if (!params->character)
		return (1);
	return (0);
}
