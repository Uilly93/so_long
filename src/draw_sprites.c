/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:08:18 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 13:18:02 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	put_wall(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->walls, x * TILE_SIZE, y * TILE_SIZE);
}

void	put_floor(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->floor, x * TILE_SIZE, y * TILE_SIZE);
}

void	put_collectibles(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->collectibles, x * TILE_SIZE, y * TILE_SIZE);
}

void	put_character(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->character, x * TILE_SIZE, y * TILE_SIZE);
}

void	put_exit(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->exit, x * TILE_SIZE, y * TILE_SIZE);
}
