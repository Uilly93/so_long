/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:35:52 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 11:02:32 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	get_check_pos(t_utils *params, t_check *check)
{
	int	i;

	i = 0;
	check->map = ft_calloc(params->map_height + 1, sizeof(char *));
	if (!check->map)
		return ;
	while (i < params->map_height)
	{
		check->map[i] = ft_strdup(params->map[i]);
		i++;
	}
	check->pos_x = params->pos_x;
	check->pos_y = params->pos_y;
	check->max_x = params->map_width;
	check->max_y = params->map_height - 1;
}

int	flood_fill(t_check *map, int x, int y)
{
	if (x < 0 || x > map->max_x || y < 0 || y > map->max_y)
		return (1);
	if (map->map[y][x] == '1' || map->map[y][x] == 'c')
		return (1);
	else
		map->map[y][x] = 'c';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
	return (0);
}

int	check_after_filled(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'C' || map[i][j] == 'E')
			{
				write(2, "Error:\nMap can't be finished\n", 29);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
