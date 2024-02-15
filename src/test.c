/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/15 15:57:31 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include <unistd.h>

int	check_error(t_utils *params);

int	check_line(t_utils *params);

void	display_door(t_utils *params); // LEAK

void	display_character(t_utils *params); // LEAK

void	destroy_images_map(t_utils *params, t_check *check);

void    ft_draw_sprite(t_utils *params, t_img *img, int x, int y);

int		updating(void *params);

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

int	quit_game(t_utils *params)
{
	mlx_loop_end(params->mlx_ptr);
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

void	print_character(t_utils *params, int x, int y);

void	check_exit(t_utils *params)
{
	if (params->map[params->map_y][params->map_x] == 'E')
		{
			params->door_x = params->map_x;
			params->door_y = params->map_y;
			params->door_count += 1;
		}
}

void	check_character(t_utils *params)
{
	if (params->map[params->map_y][params->map_x] == 'P')
		{
			params->pos_x = params->map_x;
			params->pos_y = params->map_y;
			params->nb_character += 1;
		}
}

void	check_collectibles(t_utils *params)
{
	if(params->map[params->map_y][params->map_x] == 'C')
		params->collected += 1;
}

int	check_input(char c)
{
	if (c != '1' && c != '0' && c != 'E' && c != 'C' && c != 'P' && c != '\n')
		return (1);
	return (0);
}

int	check_map(t_utils *params)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(params->map[i])
	{
		j = 0;
		while(params->map[i][j])
		{
			if(check_input(params->map[i][j]) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
void	get_check_pos(t_utils *params, t_check *check)
{
	int i;
	
	i = 0;
	check->map = ft_calloc(params->map_height + 1, sizeof(char *));
	if(!check->map)
		return ;
	while(i < params->map_height)
	{
		check->map[i] = ft_strdup(params->map[i]);
		i++;
	}
	check->pos_x = params->pos_x;
	check->pos_y = params->pos_y;
}
void print_map(char **map)
{
	int i;

	i = 0;
	while(map[i])
		ft_putstr(map[i++]);
}

void	flood_fill(char **map, int x, int y)
{
	if(map[x][y] == '1' || map[x][y] == 'c')
		return ;
	else
		map[x][y] = 'c';
	flood_fill(map, x + 1, y);
	flood_fill(map, x - 1, y);
	flood_fill(map, x, y + 1);
	flood_fill(map, x, y - 1);
	return ;
}

int check_after_filled(char **map)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while(map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if(map[i][j] == 'C' || map[i][j] == 'E')
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

int	get_pos(t_utils *params ,t_check *check)
{
	// if (check_line(params))
	// 	return (1);
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
	flood_fill(check->map, check->pos_x, check->pos_y);
	if(check_after_filled(check->map))
		return(1);
	return (0);
}
// void	print_map(t_check *check)
// {
	
// }



void	display_character(t_utils *params)
{
	put_floor(params, params->pos_x, params->pos_y);
	if(params->pos_x == params->door_x && params->pos_y == params->door_y)
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
	if(params->collected == 0)
	{
		mlx_destroy_image(params->mlx_ptr, params->exit);
		params->exit = mlx_xpm_file_to_image(params->mlx_ptr, \
		"src/textures/open.xpm", &w, &h);
	}
	put_exit(params, params->door_x, params->door_y);
}

int	get_key(int key, t_utils *params);

int	ft_display_map(t_utils *params)
{
	display_sprites(params);
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, \
												params->canvas, 0, 0);
	return (0);
}

void	load_sprites(t_utils *params)
{
	int height = TILE_SIZE;
	int width = TILE_SIZE;
	
	params->walls = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/wall.xpm", &width, &height);
	if(!params->walls)
		return ;
	params->floor = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/floor.xpm", &width, &height);
	if(!params->floor)
		return ;
	params->collectibles = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/collectible.xpm", &width, &height);
	if(!params->collectibles)
		return ;
	params->character = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/p.xpm", &width, &height);
	if(!params->character)
		return ;
	params->exit = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/exit.xpm", &width, &height);
	if(!params->exit)
		return ;
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

int	parsing_line_count(t_utils *params, char *path)
{
	int		fd;
	char 	*line;

	fd = open(path, O_RDONLY | O_DIRECTORY);
	if (fd != -1)
		return (close(fd), -1);
	fd = open(path, O_RDONLY);
	if(fd < 0)
		return (1);
	line = get_next_line(fd);
	if(!line)
		return(1);
	while(line)
	{
		free(line);
		line = get_next_line(fd);
		params->map_height++;
	}
	close(fd);
	return (0);
}
int	check_walls(t_utils *params)
{
	int i;
	
	i = 0;
	while (i < params->map_width)
	{
		if (params->map[0][i] != '1')
			return (1);
		i++;
	}
	i = 0;
	while (i < params->map_width)
	{
		if (params->map[params->map_height - 1][i] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_map_edges(t_utils *params)
{
	int i;

	i = 0;
	while (i < params->map_height - 1)
	{
		if(params->map[i][0] != '1' || 
				params->map[i][ft_strlen(params->map[i]) - 2] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_line(t_utils *params)
{
	int i;

	i = 0;
	if(!params->map)
		return (1);
	while (i < params->map_height - 1)
	{
		if((int)ft_strlen(params->map[i]) - 1 == params->map_width)
		{
			if(params->map[i][ft_strlen(params->map[i]) - 1] != '\n')
				return (1);
			i++;
		}
		else
			return (1);
	}
	if (check_walls(params) || check_map_edges(params))
		return (1);
	return (0);
}

int	parsing_map(t_utils *params, char *path)
{
	int 	fd;
	int 	i;
	char 	*line;

	i = 0;
	fd = open(path, O_RDONLY);
	if(fd < 0)
		return (1);
	if(parsing_line_count(params, path))
		return (1);
	params->map = ft_calloc(params->map_height + 1, sizeof(char *));
	if(!params->map)
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


void	update_collectibles(t_utils *params)
{
	if (params->map[params->pos_y][params->pos_x] == 'C')
	{
		params->map[params->pos_y][params->pos_x] = '0';
		params->collected -= 1;
		if(params->collected > 1)
			ft_printf("%d Sukuna's fingers remaining.\n", \
						params->collected);
		else if(params->collected == 1)
			ft_printf("%d Sukuna's finger remaining.\n", \
						 params->collected);
		else if (params->collected == 0)
			ft_printf("you have eaten all Sukuna's " \
						"fingers now go to the exit\n");
	}
}

void	update_pos(t_utils *params)
{
	params->step += 1;
	ft_printf("steps : %d\n", params->step);
}
int	check_error(t_utils *params)
{
	if (check_map(params))
		return (write(2, "Error:\nInvalid map input\n", 25), 1);
	if ((params->map_width > 20) || (params->map_height > 12))
		return (write(2, "Error:\nToo big\n", 15), 1);
	if (check_line(params))
		return (write(2, "Error:\nInvalid map\n", 19), 1);
	if (params->nb_character != 1)
		return (write(2, "Error:\nYou need to have only 1 character\n", 41), 1);
	if (params->collected < 1)
		return (write(2, "Error:\nMap needs at least 1 collectible\n", 40), 1);
	if (params->door_count != 1)
		return (write(2, "Error:\nMap needs at least 1 exit door\n", 38), 1);
	return (0);
}

void	switch_sprite(t_utils *params, int nb)
{
	int h;
	int w;

	h = TILE_SIZE;
	w = TILE_SIZE;
	if(nb == 1)
	{
		mlx_destroy_image(params->mlx_ptr, params->character);
		params->character = mlx_xpm_file_to_image(params->mlx_ptr, \
												"src/textures/p.xpm", &w, &h);
	}
	if(nb == 0)
	{
		mlx_destroy_image(params->mlx_ptr, params->character);
		params->character = mlx_xpm_file_to_image(params->mlx_ptr, \
												"src/textures/rp.xpm", &w, &h);
	}
}

void	move_character(int key, t_utils *params)
{
		put_floor(params, params->pos_x, params->pos_y);
	if (key == XK_w && params->map[params->pos_y - 1][params->pos_x] != '1')
	{
		params->pos_y -= 1;
		update_pos(params);
	}
	if (key == XK_s && params->map[params->pos_y + 1][params->pos_x] != '1')
	{
		params->pos_y += 1;
		update_pos(params);
	}
	if (key == XK_a && params->map[params->pos_y][params->pos_x - 1] != '1')
	{
		switch_sprite(params, 0);
		params->pos_x -= 1;
		update_pos(params);
	}
	if (key == XK_d && params->map[params->pos_y][params->pos_x + 1] != '1')
	{
		switch_sprite(params, 1);
		params->pos_x += 1;
		update_pos(params);
	}
	update_collectibles(params);
}
// int	flood_fill(t_utils *params, int x, int y)
// {
// 	int tmp_c;
// 	int tmp_e;

// 	tmp_c = 0;
// 	tmp_e = 0;
// 	x = params->pos_x;
// 	y = params->pos_y;
// 	if()
// }

int	get_key(int key, t_utils *params)
{
	move_character(key, params);
	update_collectibles(params);
	if (params->collected == 0 && params->pos_x == params->door_x 
	&& params->pos_y == params->door_y)
	{
		ft_printf("Congratulations, you've finished the game ! " \
					"If you havn't watched Jujutsu Kaisen yet go for it\n");
		quit_game(params);
	}
	if (key == XK_Escape)
		quit_game(params);
	return (0);
}
int	init_window_hooks(t_utils *params, t_check *check)
{
	if(get_pos(params, check))
		return (1);
	params->mlx_ptr =  mlx_init();
	if (!params->mlx_ptr)
		return(1);
	params->win_ptr = mlx_new_window(params->mlx_ptr, WINDOW_WIDTH,\
										WINDOW_HEIGHT, "so_long");
	if (!params->win_ptr)
		return(1);
	params->canvas = mlx_new_image(params->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	load_sprites(params);
	mlx_hook(params->win_ptr, DestroyNotify, 0, quit_game, params);
	mlx_loop_hook(params->mlx_ptr, ft_display_map, params);
	mlx_key_hook(params->win_ptr, get_key, params);
	mlx_loop(params->mlx_ptr);
	return (0);
}

void destroy_images_map(t_utils *params, t_check *check)
{
	if(params->character)
		mlx_destroy_image(params->mlx_ptr, params->character);
	if(params->floor)
		mlx_destroy_image(params->mlx_ptr, params->floor);
	if(params->walls)
		mlx_destroy_image(params->mlx_ptr, params->walls);
	if(params->collectibles)
		mlx_destroy_image(params->mlx_ptr, params->collectibles);
	if(params->exit)
		mlx_destroy_image(params->mlx_ptr, params->exit);
	if(params->canvas)
		mlx_destroy_image(params->mlx_ptr, params->canvas);
	if(params->map)
		ft_free_map(params->map);
	if(check->map)
		ft_free_map(check->map);
	if(params->win_ptr)
		mlx_destroy_window(params->mlx_ptr, params->win_ptr);
	if(params->mlx_ptr)
		mlx_destroy_display(params->mlx_ptr);
	if(params->mlx_ptr)
		free(params->mlx_ptr);
}

int main(int ac, char **av)
{
	t_utils	params;
	t_check check;

	ft_bzero(&params, sizeof(params));
	ft_bzero(&check, sizeof(params));
	if(ac == 2)
	{
		if(parsing_map(&params, av[1]))
		{
			write(2, "Error:\nIncorrect map path\n", 26);
			return (1);
		}
		if(!params.map)
			return (1);
		if(init_window_hooks(&params, &check))
		{
			destroy_images_map(&params, &check);
			exit(0);
		}
		else
			destroy_images_map(&params, &check);
	}
	return (0);
}
