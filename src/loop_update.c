/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:23:01 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 11:07:34 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	update_collectibles(t_utils *params)
{
	if (params->map[params->pos_y][params->pos_x] == 'C')
	{
		params->map[params->pos_y][params->pos_x] = '0';
		params->collected -= 1;
		if (params->collected > 1)
			ft_printf("%d Sukuna's fingers remaining.\n", \
						params->collected);
		else if (params->collected == 1)
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

int	move_character(int key, t_utils *params)
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
	return (0);
}

int	get_key(int key, t_utils *params)
{
	if (move_character(key, params))
		return (1);
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
