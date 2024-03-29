/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:15:16 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 13:20:50 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	parsing_line_count(t_utils *params, char *path)
{
	int		fd;
	char	*line;

	fd = open(path, O_RDONLY | O_DIRECTORY);
	if (fd != -1)
		return (close(fd), -1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		params->map_height++;
	}
	close(fd);
	return (0);
}

int	parsing_map(t_utils *params, char *path)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	if (parsing_line_count(params, path))
		return (1);
	params->map = ft_calloc(params->map_height + 1, sizeof(char *));
	if (!params->map)
		return (close(fd), 1);
	line = get_next_line(fd);
	if (!line)
		return (close(fd), 1);
	params->map[i++] = line;
	while (line)
	{
		line = get_next_line(fd);
		params->map[i++] = line;
	}
	params->map_width = ft_strlen(params->map[0]) - 1;
	close(fd);
	return (0);
}

void	identify_sprites(t_utils *params, int x, int y)
{
	if (params->map[y][x] == '1')
		put_wall(params, x, y);
	if (params->map[y][x] == '0')
		put_floor(params, x, y);
	if (params->map[y][x] == 'C')
	{
		put_floor(params, x, y);
		put_collectibles(params, x, y);
	}
	if (params->map[y][x] == 'E')
	{
		put_floor(params, x, y);
		put_exit(params, x, y);
	}
	display_door(params);
	display_character(params);
}

void	ft_draw_sprite(t_utils *params, t_img *img, int x, int y)
{
	int				i;
	int				j;
	unsigned int	color;

	if (!img)
		return ;
	i = 0;
	while (i < img->width)
	{
		j = -1;
		while (++j < img->height)
		{
			if (j + y < 0 || j + y >= params->map_height * TILE_SIZE
				|| i + x < 0 || i + x >= params->map_width * TILE_SIZE)
				continue ;
			color = ((int *)img->data)[(int)(j) *img->width + (int)(i)];
			if (color == 0xFF000000)
				continue ;
			((int *)params->canvas->data)[(y + j) * params->canvas->width
				+ (x + i)] = color;
		}
		i++;
	}
}
