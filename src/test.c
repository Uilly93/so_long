/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/06 16:59:32 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// int	*call_end(t_utils *params)
// {
// 	mlx_loop_end(params->mlx_ptr);
// 	return (0);
// }

int	updating(void *params);

int	quit_game(t_utils *params)
{
	mlx_loop_end(params->mlx_ptr);
	return (0);
}

void	display_background(t_utils *params)
{
	int height = 154;
	int width = 465;
	
	params->path_sprites = "src/sprites/background.xpm";
	params->sprites = mlx_xpm_file_to_image(params->mlx_ptr, params->path_sprites, &width, &height);
	mlx_put_image_to_window(params->mlx_ptr, params->win_ptr, params->sprites, 0, 0);
	// free(params->path_sprites);
}



void close_window(t_utils *params)
{
	mlx_hook(params->win_ptr, 17, 0, quit_game, &params);
}

char **parsing_map(t_utils *params)
{
	int 	fd;
	char 	*tmp;
	int 	i;

	i = 0;
	fd = open("src/map.ber", O_RDONLY);
	while(params->map)
	{
		params->map = ft_calloc(1 + i, sizeof(char *));
		params->map[i] = get_next_line(fd);
		i++;
	}
	return (params->map);
}

int	get_key(int key, t_utils *params)
{
	
	ft_printf("%d\n", key);
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
	mlx_key_hook(params->win_ptr, get_key, params);
	mlx_hook(params->win_ptr, DestroyNotify, 0, quit_game, params);
	display_background(params);
	mlx_loop(params->mlx_ptr);
	return (0);
}



int main(void)
{
	t_utils	params;

	init_window_hooks(&params);
	mlx_destroy_window(params.mlx_ptr, params.win_ptr);
	mlx_destroy_display(params.mlx_ptr);
	free(params.mlx_ptr);
	// free(params.sprites);
	// free(params.path_sprites);
}
