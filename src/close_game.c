/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:25:53 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 11:06:05 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	quit_game(t_utils *params)
{
	mlx_loop_end(params->mlx_ptr);
	return (0);
}

void	close_window(t_utils *params)
{
	mlx_hook(params->win_ptr, 17, 0, quit_game, &params);
}

void	ft_free_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	destroy_images_map(t_utils *params, t_check *check)
{
	if (params->character)
		mlx_destroy_image(params->mlx_ptr, params->character);
	if (params->floor)
		mlx_destroy_image(params->mlx_ptr, params->floor);
	if (params->walls)
		mlx_destroy_image(params->mlx_ptr, params->walls);
	if (params->collectibles)
		mlx_destroy_image(params->mlx_ptr, params->collectibles);
	if (params->exit)
		mlx_destroy_image(params->mlx_ptr, params->exit);
	if (params->canvas)
		mlx_destroy_image(params->mlx_ptr, params->canvas);
	if (params->map)
		ft_free_map(params->map);
	if (check->map)
		ft_free_map(check->map);
	if (params->win_ptr)
		mlx_destroy_window(params->mlx_ptr, params->win_ptr);
	if (params->mlx_ptr)
		mlx_destroy_display(params->mlx_ptr);
	if (params->mlx_ptr)
		free(params->mlx_ptr);
}
