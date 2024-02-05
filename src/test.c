/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 14:10:05 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/05 17:07:50 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	call_end(t_utils *params)
{
	mlx_loop_end(params->mlx_ptr);
	return (0);
}

int	updating(t_utils *params)
{
	
}

int main(void)
{
	void	*mlx;
	void	*win;

	t_utils	*infos;

	mlx = mlx_init();
	win = mlx_new_window(infos->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "window");
	infos->mlx_ptr = mlx;
	infos->win_ptr = win;
	mlx_loop(infos->mlx_ptr);
	mlx_loop_hook(infos->mlx_ptr, );
	mlx_hook(infos->win_ptr, 17, 0, call_end(infos));
	if(mlx_key_hook(infos->win_ptr, mlx_loop_end(infos->mlx_ptr), ))
	{
	mlx_destroy_window(infos->mlx_ptr, infos->win_ptr);
	mlx_destroy_display(infos->mlx_ptr);
	free(infos->mlx_ptr);
	}
}