/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 10:28:45 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/18 10:30:07 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_error(t_utils *params)
{
	if (check_map(params))
		return (write(2, "Error:\nInvalid map.\n", 20), 1);
	if ((params->map_width > 20) || (params->map_height > 11))
		return (write(2, "Error:\nInvalid map.\n", 20), 1);
	if (check_line(params))
		return (write(2, "Error:\nInvalid map.\n", 20), 1);
	if (params->nb_character != 1)
		return (write(2, "Error:\nInvalid map.\n", 20), 1);
	if (params->collected < 1)
		return (write(2, "Error:\nInvalid map.\n", 20), 1);
	if (params->door_count != 1)
		return (write(2, "Error:\nInvalid map.\n", 20), 1);
	return (0);
}
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
	if (params->map[params->map_y][params->map_x] == 'C')
		params->collected += 1;
}
