/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:08:18 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 10:08:56 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void    ft_draw_sprite(t_utils *params, t_img *img, int x, int y)
{
    int                i;
    int                j;
    unsigned int    color;

	if (!img)
		return ;
    i = 0;
    while (i < img->width)
    {
        j = -1;
        while (++j < img->height)
        {
            if (j + y < 0 || j + y >= params->map_height * TILE_SIZE || i + x < 0
									|| i + x >= params->map_width * TILE_SIZE)
                continue;
            color = ((int *)img->data)[(int)(j) * img->width + (int)(i)];
            if (color == 0xFF000000)
                continue;
            ((int *)params->canvas->data)[(y + j) * params->canvas->width + 
																(x + i)] = color;
        }
        i++;
    }
}

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
