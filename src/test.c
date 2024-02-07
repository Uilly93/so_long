/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/07 17:33:05 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	*call_end(t_utils *params)
// {
// 	mlx_loop_end(params->mlx_ptr);
// 	return (0);
// }

void    ft_draw_sprite(t_utils *params, t_img *img, int x, int y);

int		updating(void *params);

void	ft_put_wall(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->walls, x * TILE_SIZE, y * TILE_SIZE);
	// mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->walls, x * TILE_SIZE, y * TILE_SIZE);
}
void	ft_put_floor(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->floor, x * TILE_SIZE, y * TILE_SIZE);
	// mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->floor, x * TILE_SIZE, y * TILE_SIZE);
}

void	ft_put_collectibles(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->collectibles, x * TILE_SIZE, y * TILE_SIZE);
	// mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->collectibles, x * TILE_SIZE, y * TILE_SIZE);
}

void	ft_put_character(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->character, x * TILE_SIZE, y * TILE_SIZE);
	// mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->character, x * TILE_SIZE, y * TILE_SIZE);
}

void	ft_put_exit(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->exit, x * TILE_SIZE, y * TILE_SIZE);
	// mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->exit, x * TILE_SIZE, y * TILE_SIZE);
}

void    ft_draw_sprite(t_utils *params, t_img *img, int x, int y)
{
    int                i;
    int                j;
    unsigned int    color;

    i = 0;
    while (i < img->width)
    {
        j = 0;
        while (j < img->height)
        {
            if (j + y < 0 || j + y >= params->map_height * TILE_SIZE || i + x < 0 || i + x >= params->map_width * TILE_SIZE)
            {
                j++;
                continue;
            }
            color = ((int *)img->data)[(int)(j) * img->width + (int)(i)];
            if (color == 0xFF000000)
            {
                j++;
                continue;
            }
            ((int *)params->canvas->data)[(y + j) * params->canvas->width + (x + i)] = color;
            j++;
        }
        i++;
    }
}

int	quit_game(t_utils *params)
{
	mlx_loop_end(params->mlx_ptr);
	return (0);
}

int	display_walls(t_utils *params) // LEAK
{
	int x = 0;
	int y = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (params->map[y][x] == '1')
				ft_put_wall(params, x, y);
			x++;
		}
		y++;
	}
	// free(params->path_sprites);
	return (0);
}

int	display_floor(t_utils *params) // LEAK
{
	int x = 0;
	int y = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (params->map[y][x] == '0')
				ft_put_floor(params, x, y);
			x++;
		}
		y++;
	}
	// free(params->path_sprites);
	return (0);
}

int	display_collectible(t_utils *params) // LEAK
{
	int x = 0;
	int y = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (params->map[y][x] == 'C')
			{
				ft_put_floor(params, x, y);
				ft_put_collectibles(params, x, y);
			}
			x++;
		}
		y++;
	}
	// free(params->path_sprites);
	return (0);
}

int	display_character(t_utils *params) // LEAK
{
	int x = 0;
	int y = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (params->map[y][x] == 'P')
			{
				ft_put_floor(params, x, y);
				ft_put_character(params, x, y);
				// ft_put_collectibles(params, x, y);
			}
			x++;
		}
		y++;
	}
	// free(params->path_sprites);
	return (0);
}

int	ft_display_map(t_utils *params)
{

	display_floor(params);
	display_walls(params);
	display_collectible(params); // LEAK
	display_character(params); // LEAK
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->canvas, 0, 0);
	return (0);
}

void	load_sprites(t_utils *params)
{
	int height = TILE_SIZE;
	int width = TILE_SIZE;
	
	params->walls = mlx_xpm_file_to_image(params->mlx_ptr, "src/sprites/wall.xpm", &width, &height);
	params->floor = mlx_xpm_file_to_image(params->mlx_ptr, "src/sprites/floor.xpm", &width, &height);
	params->collectibles = mlx_xpm_file_to_image(params->mlx_ptr, "src/sprites/collectible.xpm", &width, &height);
	params->character = mlx_xpm_file_to_image(params->mlx_ptr, "src/sprites/character.xpm", &width, &height);
}

void close_window(t_utils *params)
{
	mlx_hook(params->win_ptr, 17, 0, quit_game, &params);
}

void	ft_free_map(char **map)
{
	int i;
	
	i = 0;
	while(map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	parsing_line_count(void)
{
	int		fd;
	int 	count;
	char 	*line;

	count = 0;
	fd = open("src/map.ber", O_RDONLY);
	if(fd < 0)
		return (0);
	while((line = get_next_line(fd)) != NULL)
	{
		free(line);
		count++;
	}
	if(line)
		free(line);
	close(fd);
	return (count);
}

char **parsing_map(t_utils *params) // inclure struc params->map
{
	int 	fd;
	int 	i;
	char 	*line;
	char	**tmp_map;

	i = 0;
	tmp_map = NULL;
	fd = open("src/map.ber", O_RDONLY);
	if(fd < 0)
		return (NULL);
	tmp_map = ft_calloc(parsing_line_count() + 1, sizeof(char *));
	if(!tmp_map)
		return (NULL);	
	line = get_next_line(fd);
	tmp_map[i] = line;
	i++;
	while (line)
	{
		line = get_next_line(fd);
		tmp_map[i] = line;
		i++;
	}
	params->map_width = ft_strlen(tmp_map[0]) - 1;
	params->map_height = i;
	close(fd);
	return (tmp_map);
}

// int	fill_map(t_utils *params)
// {
// 	params->map = parsing_map();
// 	while (params->map[params->map_col])
// 	{
// 		while (params->map[params->map_col][params->map_row])
// 		{
// 			if(params->map[params->map_col][params->map_row] == '1')
// 			{}
// 			else if(params->map[params->map_col][params->map_row] == '0')
// 			{}
// 			else if(params->map[params->map_col][params->map_row] == 'C')
// 			{}
// 			else if(params->map[params->map_col][params->map_row] == 'P')
// 			{}
// 			else
// 				ft_free_map(params->map);
// 			params->map_row++;
// 		}
// 		params->map_col++;
// 	}
	
// }
// void	display_map(t_utils *params)
// {
	
// }

int	get_key(int key, t_utils *params)
{
	
	// ft_printf("%d\n", key);
	if (key == XK_w){} // go up
	if (key == XK_s){} // go down
	if (key == XK_a){} // go left
	if (key == XK_d){} // go right
	if (key == XK_Escape)
		quit_game(params);
	return (0);
}
int	init_window_hooks(t_utils *params)
{
	params->mlx_ptr =  mlx_init();
	if (!params->mlx_ptr)
		return(1);
	params->win_ptr = mlx_new_window(params->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "so_long");
	if (!params->win_ptr)
		return(1);
	params->map = parsing_map(params);
	params->canvas = mlx_new_image(params->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	load_sprites(params);
	mlx_key_hook(params->win_ptr, get_key, params);
	mlx_hook(params->win_ptr, DestroyNotify, 0, quit_game, params);
	mlx_loop_hook(params->mlx_ptr, ft_display_map, params);
	// display_background(params);
	// parsing_line_count();
	// ft_printf("%d", parsing_line_count());
	mlx_loop(params->mlx_ptr);
	// ft_free_map(params->map);
	return (0);
}



int main(void)
{
	t_utils	params;
	// int		i;
	
	ft_bzero(&params, sizeof(params));

	// params.map = parsing_map();
	// i = 0;
	// while(params.map[i])
	// {
	// 	ft_printf("%s", params.map[i]);
	// 	i++;
	// }
	if(init_window_hooks(&params))
	{
		// free(params.mlx_ptr);
		exit(0);
	}
	mlx_destroy_window(params.mlx_ptr, params.win_ptr);
	mlx_destroy_display(params.mlx_ptr);
	// ft_free_map(params.map);
	free(params.mlx_ptr);
	// free(params.sprites);
	// free(params.path_sprites);
}
