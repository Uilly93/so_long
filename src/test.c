/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/09 14:54:11 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	*call_end(t_utils *params)
// {
// 	mlx_loop_end(params->mlx_ptr);
// 	return (0);
// }
int	check_error(t_utils *params);

void destroy_images_map(t_utils *params); // plus de leak !

void    ft_draw_sprite(t_utils *params, t_img *img, int x, int y);

int		updating(void *params);

void	put_wall(t_utils *params, int x, int y)
{
	ft_draw_sprite(params, params->walls, x * TILE_SIZE, y * TILE_SIZE);
	// mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->walls, x * TILE_SIZE, y * TILE_SIZE);
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
            if (j + y < 0 || j + y >= params->map_height * TILE_SIZE || i + x < 0 || i + x >= params->map_width * TILE_SIZE)
                continue;
            color = ((int *)img->data)[(int)(j) * img->width + (int)(i)];
            if (color == 0xFF000000)
                continue;
            ((int *)params->canvas->data)[(y + j) * params->canvas->width + (x + i)] = color;
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
				put_wall(params, x, y);
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
				put_floor(params, x, y);
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
				put_floor(params, x, y);
				put_collectibles(params, x, y);
			}
			x++;
		}
		y++;
	}
	return (0);
}

int	display_exit(t_utils *params) // LEAK
{
	int x = 0;
	int y = 0;
	while (params->map[y])
	{
		x = 0;
		while (params->map[y][x])
		{
			if (params->map[y][x] == 'E')
			{
				put_floor(params, x, y);
				put_exit(params, x, y);
			}
			x++;
		}
		y++;
	}
	// free(params->path_sprites);
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


int	get_pos(t_utils *params)
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
	return (0);
}

void	display_character(t_utils *params) // LEAK
{
	put_floor(params, params->pos_x, params->pos_y);
	if(params->pos_x == params->door_x && params->pos_y == params->door_y)
		put_exit(params, params->door_x, params->door_y);
	put_character(params, params->pos_x, params->pos_y);
}

void	display_door(t_utils *params) // LEAK
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

// void	print_character(t_utils *params, int x, int y)
// {
// 	display_walls(params);
// 	display_collectible(params); // LEAK
// 	display_floor(params);
// 	put_character(params, x, y);
// 	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->canvas, 0, 0);
// }

int	get_key(int key, t_utils *params);

int	ft_display_map(t_utils *params)
{
	display_floor(params);
	display_walls(params);
	display_collectible(params); // LEAK
	display_door(params);
	display_character(params);
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
	params->floor = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/floor.xpm", &width, &height);
	params->collectibles = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/collectible.xpm", &width, &height);
	params->character = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/p.xpm", &width, &height);
	params->exit = mlx_xpm_file_to_image(params->mlx_ptr, \
								"src/textures/exit.xpm", &width, &height);
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

void	update_collectibles(t_utils *params)
{
	if (params->map[params->pos_y][params->pos_x] == 'C')
	{
		params->map[params->pos_y][params->pos_x] = '0';
		params->collected -= 1;
		if(params->collected > 1)
			ft_printf("il te reste %d doigts de Sukuna a manger\n", \
						params->collected);
		else if(params->collected == 1)
			ft_printf("il te reste %d doigt de Sukuna a manger\n", \
						 params->collected);
		else if (params->collected == 0)
			ft_printf("tu as mange tout les doigts de " \
						"Sukuna diriges toi vers la sortie\n");
	}
}

// void	print_while_moving(t_utils *params)
// {
	
// }

void	update_pos(t_utils *params)
{
	params->step += 1;
	ft_printf("nombre de pas : %d\n", params->step);
}
int	check_error(t_utils *params)
{
	if (params->nb_character != 1)
		return (ft_printf("il y a trop ou aucuns personnages sur la map"), 1);
	if (params->collected < 1)
		return (ft_printf("il faut au moins un collectible pour jouer"), 1);
	if (params->door_count != 1)
		return (ft_printf("la map doit contenir une seul porte de sortie"), 1);
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

int	get_key(int key, t_utils *params)
{
	move_character(key, params);
	update_collectibles(params);
	if (params->collected == 0 && params->pos_x == params->door_x 
	&& params->pos_y == params->door_y)
	{
		ft_printf("Bravo tu as fini le jeu, " \
					"si tu n'a pas encore vu Jujutsu Kaisen fonce le voir\n");
		quit_game(params);
	}
	if (key == XK_Escape)
		quit_game(params);
	return (0);
}
int	init_window_hooks(t_utils *params)
{
	params->mlx_ptr =  mlx_init();
	if (!params->mlx_ptr)
		return(1);
	params->win_ptr = mlx_new_window(params->mlx_ptr, WINDOW_WIDTH,\
										WINDOW_HEIGHT, "so_long");
	if (!params->win_ptr)
		return(1);
	params->map = parsing_map(params);
	if(!params->map)
		return (1);
	get_pos(params);
	if(check_error(params))
		return (1);
	params->canvas = mlx_new_image(params->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	load_sprites(params);
	mlx_hook(params->win_ptr, DestroyNotify, 0, quit_game, params);
	mlx_loop_hook(params->mlx_ptr, ft_display_map, params);
	mlx_key_hook(params->win_ptr, get_key, params);
	mlx_loop(params->mlx_ptr);
	return (0);
}

void destroy_images_map(t_utils *params) // plus de leak !
{
	// quit_game(params);
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
	if(params->win_ptr)
		mlx_destroy_window(params->mlx_ptr, params->win_ptr);
	if(params->mlx_ptr)
		mlx_destroy_display(params->mlx_ptr);
	if(params->mlx_ptr)
		free(params->mlx_ptr);
}

int main(void)
{
	t_utils	params;
		
	ft_bzero(&params, sizeof(params));
	if(init_window_hooks(&params))
	{
		destroy_images_map(&params);
		exit(0);
	}
	else
		destroy_images_map(&params);
}
